#include "ofApp.h"

#include "ParticleGravity.h"
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
    for (auto particle = tabParticle.begin(); particle != tabParticle.end();)
    {
        // Check if the particle is out of the screen
        if ((*particle)->position.y < -RAD || (*particle)->position.x > static_cast<float>(ofGetWidth()) + RAD)
        {
            // If so, delete the particle and release the memory
            delete *particle;
            // Remove the particle from the list
            particle = tabParticle.erase(particle);
        }
        else
        {
            // Else, go to the next particle
            ++particle;
        }
    }
}

/**
 * @brief Return the new velocity of the Particle 1 when in collision with the Particle 2
 *
 */
Vector ofApp::UpdateCollision(float e, Particle p1, Particle p2)
{
    Vector n = (p2.position - p1.position).normalized();
    float K = n*(p1.velocity - p2.velocity)*(e+1)/(p1.getInversedMass() + p2.getInversedMass());
    //auto P = p1.velocity * p1.getMass();
    return p1.velocity - n*K*p1.getInversedMass();
}

/**
 * @brief Check all the collisions between each particle
 *
 */
void ofApp::checkCollision()
{
    float e = 0.9f;
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
                Particle *p1Copy = p1->duplicate();
                
                p1->velocity = UpdateCollision(e, *p1, *p2);
                
                // Application de la force sur P2
                p2->velocity = UpdateCollision(e, *p2, *p1Copy);


                
            }
            ++tests;

            ++particle2;
        }
        ++particle1;
    }
    if (numCollisions)
        cout << "Number of collisions: " << numCollisions << "\r" << flush;
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    checkUnboundParticules();
    checkCollision();
    if (simPause) return;
    // Set the delta time using the last frame time
    updateParticles(tabParticle, ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Drawing the cursor for initial velocity
    Vector tempOrigin = Vector(particleOrigin.x, ofGetHeight() - particleOrigin.y);
    Vector tempVelocity = Vector(particleVelocity.x, ofGetHeight() - particleVelocity.y);
    ofSetColor(OF_CONSOLE_COLOR_GREEN);
    ofDrawCircle(tempOrigin.v2(), RAD/2);
    ofSetColor(255, 255, 255);
    ofDrawLine(tempOrigin.v2(),tempVelocity.v2());
    // Drawing the particles
    for (Particle* p : tabParticle)
    {
        ofSetColor(p->color[0], p->color[1], p->color[2]);
        Vector realPos = Vector(p->position.x, ofGetHeight() - p->position.y);
        ofDrawCircle(realPos.v2(), p->radius);
        ofSetColor(255, 255, 255);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case ' ':
        break;
    case 'p':
        simPause = !simPause;
        cout << (!simPause ? "Unpaused" : "Paused") << endl;
        break;
    case 'i':
        clearParticles();
        break;
    case 'o':
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
        currentParticle = Particle(particleVelocity, 2, 0, 255, 0, 2); 
        break;
    case 'e':
        cout << "Heavy bullet" << endl;
        currentParticle = Particle(particleVelocity, 3, 50.0f, 15.0f);  
        break;
    case 'r':
        cout << "Very heavy bullet" << endl;
        currentParticle = Particle(particleVelocity, 4, 100.0f, 20.0f); 
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
    default:
        break;
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
            particleVelocity = Vector(x, ofGetHeight() -  y);
            currentParticle.velocity.x = particleVelocity.x - particleOrigin.x;
            currentParticle.velocity.y = particleVelocity.y - particleOrigin.y;
            break;
        case OF_MOUSE_BUTTON_RIGHT:
            particleOrigin = Vector(x,ofGetHeight()-y,0);
            particleVelocity = Vector(x,ofGetHeight()-y,0);
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
    ParticleGravity pg;
    pg.setGravity(Vector(0,-9.81,0));
   
    // Iterates over the list of particles
    for (Particle* p : tabParticle)
    {
        pg.updateForce(p,deltaT);
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