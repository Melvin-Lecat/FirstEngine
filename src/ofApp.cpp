#include "ofApp.h"

#include "ParticleGravity.h"
#include "ParticleSpringHook.h"
#include "FixedSpringGenerator.h"
#include "ParticleFriction.h"
#include "ParticleSpringGenerator.h"
#define RAD 15

//--------------------------------------------------------------
void ofApp::setup()
{
    // Set the color of the items
    ofSetColor(255, 255, 255);
    // Present the user manual
    cout << "User Manual:\n"
        "\tPress 'p' to pause simulation\n"
        "\tPress 'i' to clear all bullets\n"
        "\tPress 'o' to fire the current bullet (default : standard)\n"
        "\tPress the right arrow to update frame by frame while paused\n"
        "\tClick in the window to change the initial velocity\n"
        "\tPress 'a' to fire a standard bullet\n"
        "\tPress 'z' to fire a laser like bullet\n"
        "\tPress 'e' to fire a heavy bullet\n"
        "\tPress 'r' to fire a very heavy bullet\n"
        "\tPress 't' to fire a custom bullet\n"
        << endl;
}

/**
 * @brief Check if the particles are out of the screen and delete them
 * 
 */
void ofApp::checkUnboundParticules()
{
    // Iterates over the list of particles
    for (auto particule = tabParticle.begin(); particule != tabParticle.end();)
    {
        // Check if the particle is out of the screen
        if ((*particule)->position.y < -RAD || (*particule)->position.x > static_cast<float>(ofGetWidth()) + RAD)
        {
            // If so, delete the particle and release the memory
            delete *particule;
            // Remove the particle from the list
            particule = tabParticle.erase(particule);
        }
        else
        {
            // Else, go to the next particle
            ++particule;
        }
    }
}

/**
 * @brief Return the new velocity of the Particle 1 when in collision with the Particle 2
 *
 */
Vector ofApp::UpdateCollision(float e, Particle *p1, Particle p2)
{
    Vector n = (p2.position - p1->position).normalized();
    float K = n * (p1->velocity - p2.velocity) * (e + 1) / (p1->getInversedMass() + p2.getInversedMass());
    //auto P = p1.velocity * p1.getMass();
    auto updatedVelocity = p1->velocity - n * K * p1->getInversedMass();
    auto move = updatedVelocity.normalized()*glm::abs((p1->radius+p2.radius) - p1->position.distance(p2.position));
    p1->position += move*  (p1->getMass() / (p1->getMass() + p2.getMass()));
    return updatedVelocity;
}

/**
 * @brief Check all the collisions between each particle
 *
 */
void ofApp::checkCollision()
{
    float e = 0.9;
    int numCollisions = 0;
    int tests = 0;
    // Iterates over the list of particles
    for (auto particle1 = tabParticle.begin(); particle1 != tabParticle.end();)
    {
        // Iterates over the list of particles not yet checked
        for (auto particle2 = tabParticle.begin(); particle2 != particle1;)
        {
            // Gets the distance and the minimal distance between the particles (squared values to be faster)
            float d = ((*particle1)->position - (*particle2)->position).squaredMagnitude();
            float minD = glm::pow2((*particle1)->radius + (*particle2)->radius);

            // Collision only if the distance is lower than the minimal distance
            
            if (d <= minD)
            {
                ++numCollisions;
                Particle* p1 = (*particle1);
                Particle* p2 = (*particle2);
                // P' = P + Kn
                // Applica1tion de la force sur P1
                Particle* p1Copy = p1->duplicate();

                p1->velocity = UpdateCollision(e, p1, *p2);

                // Application de la force sur P2
                p2->velocity = UpdateCollision(e, p2, *p1Copy);
            }
            ++tests;

            ++particle2;
        }
        ++particle1;
    }
    if (numCollisions)
        cout << "Number of collisions: " << numCollisions << "\r" << flush;
}

void ofApp::checkBoundaries()
{
    float f = -1;
    for (auto p : tabParticle)
    {
        if (p->position.x < RAD)
        {
            p->velocity.x *= f;
        }
        if (p->position.x > ofGetWidth() - RAD)
        {
            p->velocity.x *= f;
        }
        if (p->position.y < RAD)
        {
            p->velocity.y *= f;
        }
        if (p->position.y > ofGetHeight() - RAD)
        {
            p->velocity.y *= f;
        }
    }
}

void ofApp::updateForces()
{
    if (!blobgame)
    {
        ParticleGravity pg(Vector(0, -9.81, 0));
        FixedSpringGenerator sg(Vector(ofGetWidth() / 2, ofGetHeight() / 2, 0), .7, 20);
        ParticleFriction pf(0.1, 0.2);
        for (auto p : tabParticle)
        {
            particleForceRegistry.add(p, &pg);
            //particleForceRegistry.add(p,&sg);
            particleForceRegistry.add(p, &pf);
        }
    }
    else
    {
        for (auto p = tabParticle.begin(); p != tabParticle.end(); p++)
        {
            /*if (*p == tabParticle.front())
            {
                continue;
            }*/
            FixedSpringGenerator fsg(mainParticle.position, 200, 20);
            ParticleFriction pf(0.1, 0.2);
            particleForceRegistry.add(*p, &pf);
            particleForceRegistry.add(*p, &fsg);
        }
    }
    
    particleForceRegistry.updateForces(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::update()
{
    checkCollision();
    //checkUnboundParticules();
    checkBoundaries();
    if (simPause) return;
    // Set the delta time using the last frame time7
    updateForces();
    updateParticles(tabParticle, ofGetLastFrameTime());
}

void ofApp::DrawParticle(Particle p)
{
    ofSetColor(p.color[0], p.color[1], p.color[2]);
    Vector realPos = Vector(p.position.x, ofGetHeight() - p.position.y);
    ofDrawCircle(realPos.v2(), p.radius);
    ofSetColor(255, 255, 255);
}

void ofApp::DrawSystem()
{
    ofSetColor(OF_CONSOLE_COLOR_YELLOW);
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, RAD);
    // Drawing the cursor for initial velocity
    Vector tempOrigin = Vector(particleOrigin.x, ofGetHeight() - particleOrigin.y);
    Vector tempVelocity = Vector(particleVelocity.x, ofGetHeight() - particleVelocity.y);
    ofSetColor(OF_CONSOLE_COLOR_GREEN);
    ofDrawCircle(tempOrigin.v2(), RAD / 2);
    ofSetColor(255, 255, 255);
    ofDrawLine(tempOrigin.v2(), tempVelocity.v2());
}

void ofApp::DrawParticles()
{
    if(blobgame)
    {
        DrawParticle(mainParticle);
    }
    // Drawing the particles
    for (Particle* p : tabParticle)
    {
        DrawParticle(*p);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    DrawSystem();
    DrawParticles();
}

void ofApp::SetupBlobGame()
{
    Vector positioncentre = Vector(ofGetWidth() / 2, ofGetHeight() / 2);
    Vector blobdroite = Vector(60, 0);
    Vector blobgauche = Vector(-60, 0);
    Vector blobhaut = Vector(0, 60);
    Vector blobbas = Vector(0, -60);
    
    clearParticles();
    blobgame = true;

    currentParticle = Particle(particleVelocity, 1, 255,255,255,15.0f);
    currentParticle.position = positioncentre;
    currentParticle.velocity = Vector(0, 0);
    mainParticle = currentParticle;
    //tabParticle.push_back(currentParticle.duplicate());
    
            
    currentParticle.position = positioncentre + blobdroite;
    tabParticle.push_back(currentParticle.duplicate());

    currentParticle.position = positioncentre + blobgauche;
    tabParticle.push_back(currentParticle.duplicate());

    currentParticle.position = positioncentre + blobhaut;
    tabParticle.push_back(currentParticle.duplicate());

    currentParticle.position = positioncentre + blobbas;
    tabParticle.push_back(currentParticle.duplicate());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
    if (blobgame)
    {
        int moveSpeed = 10;
        switch (key)
        {
        case 'z':
            //tabParticle.front()->addForce(Vector(0,10));
            mainParticle.position.y += moveSpeed;
            break;
        case 'q':
            // tabParticle.front()->addForce(Vector(-10,0));
            mainParticle.position.x -= moveSpeed;
            break;
        case 's':
            //tabParticle.front()->addForce(Vector(0,-10));
            mainParticle.position.y -= moveSpeed;
            break;
        case 'd':
            //tabParticle.front()->addForce(Vector(10,0));
            mainParticle.position.x += moveSpeed;
            break;
        case 'b':
            clearParticles();
            blobgame = false;
        //les forces aussi
            break;
        
        case 'l':
            cout << "Particles: " << tabParticle.size() << endl;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (key)
        {
        case 'p':
            simPause = !simPause;
            cout << (!simPause ? "Unpaused" : "Paused") << endl;
            break;
        case 'i':
            clearParticles();
            break;
        case 'o':
            currentParticle.position = particleOrigin;
            tabParticle.push_back(currentParticle.duplicate());
            break;
        case OF_KEY_RIGHT:
            if (simPause) { updateParticles(tabParticle, ofGetLastFrameTime()); }
            break;
        case 'a':
            cout << "Standard bullet" << endl;
            currentParticle = Particle(particleVelocity, 1, 9.81f, 10.0f);
            break;
        case 'z':
            cout << "Laser" << endl;
            currentParticle = Particle(particleVelocity, 0.5, 0, 255, 0, 2);
            break;
        case 'e':
            cout << "Heavy bullet" << endl;
            currentParticle = Particle(particleVelocity, 10, 255,255,0, 20.0f);
            break;
        case 'r':
            cout << "Very heavy bullet" << endl;
            currentParticle = Particle(particleVelocity, 100, 255,255,255, 40.0f);
            break;
        case 't':
            simPause = false;
            cout << "Custom bullet \n""Please enter the parameters \n" << endl;
            cout << "Mass: ";
            cin >> mass;
            cout << "Gravity: ";
            cin >> gravity;
            currentParticle = Particle(particleVelocity, mass, gravity);
            break;
        case 'b':
            SetupBlobGame();
            break;
        case 'l':
            cout << "Particles: " << tabParticle.size() << endl;
            break;
        default:
            break;
        
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    // Setting the initial velocity with the mouse position
    switch (button)
    {
    case OF_MOUSE_BUTTON_LEFT:
        particleVelocity = Vector(x, ofGetHeight() - y);
        currentParticle.velocity.x = particleVelocity.x - particleOrigin.x;
        currentParticle.velocity.y = particleVelocity.y - particleOrigin.y;
        break;
    case OF_MOUSE_BUTTON_RIGHT:
        particleOrigin = Vector(x, ofGetHeight() - y, 0);
        particleVelocity = Vector(x, ofGetHeight() - y, 0);
        currentParticle.setPosition(particleOrigin);
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

/**
 * @brief Update the particles with the Euler method
 * 
 * @param tabParticle the list of particles to update
 * @param deltaT the delta time
 */
void ofApp::updateParticles(std::list<Particle*> tabParticle, float deltaT)
{
    // Iterates over the list of particles
    for (Particle* p : tabParticle)
    {
        // Update the time
        p->time += deltaT;
        // Update the position
        p->eulerIntegration(deltaT);
    }
}

/**
 * @brief Remove all the particles from the list and release the memory
 * 
 */
void ofApp::clearParticles()
{
    cout << "Clear" << tabParticle.size() << endl;
    for (Particle* p : tabParticle)
    {
        delete p;
    }
    tabParticle.clear();
    cout << "Cleared" << tabParticle.size() << endl;
}
