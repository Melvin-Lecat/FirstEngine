#include "ofApp.h"

#include "ParticleGravity.h"
#include "ParticleSpringHook.h"
#include "FixedSpringGenerator.h"
#include "ParticleSpringGenerator.h"
#include "ParticleFriction.h"
#include "RodObject.h"
#include "WireObject.h"
#define RAD 15

//--------------------------------------------------------------
void ofApp::setup()
{
    // Set the color of the items
    ofSetColor(255, 255, 255);
    // Present the user manual
    cout << "User Manual:\n\n"
        "\tAppuyer sur 'p' pour mettre en pause la simulation\n"
        "\tAppuyer sur 'i' pour supprimer toutes les particules\n"
        "\tAppuyer sur la fleche de droite pour mettre a jour frame par frame la simulation lorsqu'elle est en pause\n"
        "\tUtilisez le clic gauche dans la fenetre de simulation pour changer la velocite (representee par un trait/vecteur)\n"
        "\tUtilisez le clic droti dans la fenetre de simulation pour changer la position de la particule (represente par un point)\n"
        "\tAppuyer sur 'b' pour activer ou desactiver le jeu des blobs\n\n"

        "\tSi le jeu des blobs est active\n\n"
        "\tAppuyer sur 'z' pour deplacer la particule centrale vers le haut\n"
        "\tAppuyer sur 'q' pour deplacer la particule centrale vers la gauche\n"
        "\tAppuyer sur 's' pour deplacer la particule centrale vers la droite\n"
        "\tAppuyer sur 'd' pour deplacer la particule centrale vers le bas\n\n"

        "\tSinon\n\n"
        "\tAppuyer sur 'o' pour ajouter une particule\n"
        "\tAppuyer sur 'a' pour ajouter une particule normale\n"
        "\tAppuyer sur 'z' pour ajouter une particule de type laser\n"
        "\tAppuyer sur 'e' pour ajouter une particule legerement plus lourde\n"
        "\tAppuyer sur 'r' pour ajouter une particule plus lourde\n"
        "\tAppuyer sur 't' pour ajouter une particule customisee\n"
        "\tAppuyer sur 'h' pour activer/desactiver le ressort central\n"
        "\tAppuyer sur 'j' pour activer/desactiver la gravite\n"
        "\tAppuyer sur 'l' pour activer/desactiver la friction aerienne\n\n"
    
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
        if ((*particule)->position.y < -(*particule)->radius || (*particule)->position.x > static_cast<float>(
            ofGetWidth()) + (*particule)->radius)
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
Vector ofApp::UpdateCollision(float e, Particle* p1, Particle p2)
{
    if (p1->velocity.y > -9.81 * ofGetLastFrameTime())
    {
        p1->velocity.y = 0;
    }
    Vector n = (p2.position - p1->position).normalized();
    float K = n * (p1->velocity - p2.velocity) * (e + 1) / (p1->getInversedMass() + p2.getInversedMass());
    //auto P = p1.velocity * p1.getMass();
    auto updatedVelocity = p1->velocity - n * K * p1->getInversedMass();
    auto move = /*updatedVelocity.normalized()*/n.opposite() * glm::abs(
        (p1->radius + p2.radius) - p1->position.distance(p2.position));
    p1->position += move * (p1->getMass() / (p1->getMass() + p2.getMass()));
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
}

void ofApp::checkBoundaries()
{
    float f = -1;
    for (auto p : tabParticle)
    {
        if (p->position.x < p->radius)
        {
            p->position.x += (p->radius - p->position.x);
            p->velocity.x *= f;
        }
        if (p->position.x >= ofGetWidth() - p->radius)
        {
            p->position.x -= (p->radius - glm::abs(ofGetWidth() - p->position.x));
            p->velocity.x *= f;
        }
        if (p->position.y < p->radius)
        {
            if (p->velocity.y > -9.81 * ofGetLastFrameTime())
            {
                p->position.y += (p->radius - p->position.y);
                p->velocity.y = 0;
            }
            else
            {
                p->velocity.y *= f;
            }
        }
        if (p->position.y > ofGetHeight() - p->radius)
        {
            p->position.y -= (p->radius - glm::abs(ofGetHeight() - p->position.y));
            p->velocity.y *= f;
        }
    }
}


void ofApp::updateForces()
{
    if (blobgame)
    {
        for (auto p = tabParticle.begin(); p != tabParticle.end(); p++)
        {
            /*if (*p == tabParticle.front())
            {
                continue;
            }*/
            FixedSpringGenerator fsg(mainParticle.position, 250, 50);
            ParticleFriction pf(0.1, 0.2);
            particleForceRegistry.add(*p, &pf);
            particleForceRegistry.add(*p, &fsg);
        }
    }
    else if(demo)
    {
        
    }
    else
    {
        if(enableDemo){
            WireObject wire(tabParticle.front(), tabParticle.back(), 0.7, 100);
            RodObject rod(tabParticle.front(), tabParticle.back(), 10, 200);
            FixedSpringGenerator fsg(Vector(ofGetWidth()/2,ofGetHeight()/2,0),10, 200);
            ParticleSpringGenerator psg(10,200,tabParticle.front(),tabParticle.back());
            FixedElastic fe(Vector(ofGetWidth()/2,ofGetHeight()/2,0),10, 200);
            switch (mode)
            {
            case Wire:
                cout << "wire" << endl;
                wire.CheckCollision();
                break;
            case Rod:
                rod.CheckCollision();
                break;
            case StaticSpring:
                particleForceRegistry.add(tabParticle.front(), &fsg);
                break;
            case DynamicSpring:
                particleForceRegistry.add(tabParticle.front(), &psg);
                particleForceRegistry.add(tabParticle.back(), &psg);
                break;
            case StaticElastic:
                particleForceRegistry.add(tabParticle.front(), &fe);
                break;
            default:
                break;
            
            }
            ParticleGravity pg(Vector(0, -15, 0));
            ParticleFriction pf(0.3, 0.2);
            for (auto p : tabParticle)
            {
                particleForceRegistry.add(p, &pg);
                particleForceRegistry.add(p, &pf);
            }
            
        }else
        {
            ParticleGravity pg(Vector(0, -9.81, 0));
            FixedSpringGenerator sg(Vector(ofGetWidth() / 2, ofGetHeight() / 2, 0), .7, 20);
            ParticleFriction pf(0.1, 0.2);
            for (auto p : tabParticle)
            {
                if (enableGravity) { particleForceRegistry.add(p, &pg); }
                if (enableSpring) { particleForceRegistry.add(p, &sg); }
                if (enableFriction) { particleForceRegistry.add(p, &pf); }
            }
        }
        
    }
    particleForceRegistry.updateForces(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::update()
{
    checkBoundaries();
    if (simPause) return;
    updateForces();
    updateParticles(tabParticle, ofGetLastFrameTime());
    checkCollision();
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
    if (!blobgame && !demo)
    {
        // Drawing a center cursor for debug
        if (enableSpring)
        {
            ofSetColor(0, 0, 0);
            ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 5);
        }


        // Drawing the cursor for initial velocity
        Vector tempOrigin = Vector(particleOrigin.x, ofGetHeight() - particleOrigin.y);
        Vector tempVelocity = Vector(particleVelocity.x, ofGetHeight() - particleVelocity.y);


        //Cursor circle as reference
        ofSetColor(255, 255, 255);
        ofDrawCircle(tempOrigin.v2(), RAD / 2);

        // Drawing velocity reference
        ofSetColor(255, 255, 255);
        ofDrawLine(tempOrigin.v2(), tempVelocity.v2());
    }

    if(demo)
    {
       
    }
}

void ofApp::DrawParticles()
{
    if (blobgame)
    {
        DrawParticle(mainParticle);
    }
    // Drawing the particles
    for (Particle* p : tabParticle)
    {
        if (debug)
        {
            ofSetColor(255, 0, 0);
            Vector tempOrigin = Vector(p->position.x, ofGetHeight() - p->position.y);
            Vector tempVelocity = Vector(p->velocity.x, -p->velocity.y);
            ofDrawLine(tempOrigin.v2(), (tempOrigin + tempVelocity).v2());
        }
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

    currentParticle = Particle(particleVelocity, 1, 255, 255, 255, 15.0f);
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
        float moveSpeed = 10;
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
            particleOrigin = Vector(0, 0, 0);
            blobgame = false;
            cout << "Mode Ballistique" << endl;
            break;
        case 'x':
            demo = true;
            blobgame = false;
            clearParticles();
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
        case 'd':
            debug = !debug;
            break;
        case 'o':
            if(enableDemo) clearParticles();
            enableDemo = false;
            currentParticle.position = particleOrigin;
            tabParticle.push_back(currentParticle.duplicate());
            break;
        case OF_KEY_RIGHT:
            if (simPause) { updateParticles(tabParticle, ofGetLastFrameTime()); }
            break;
        case 'a':
            cout << "Standard bullet" << endl;
            if(mode != Default) clearParticles();
            mode = Default;
            currentParticle = Particle(particleVelocity, 1, 9.81f, 10.0f);
            break;
        case 'z':
            
            cout << "Laser" << endl;
            if(mode != Default) clearParticles();
            mode = Default;
            currentParticle = Particle(particleVelocity, 0.5, 0, 255, 0, 2);
            break;
        case 'e':
            cout << "Heavy bullet" << endl;
            if(mode != Default) clearParticles();
            mode = Default;
            currentParticle = Particle(particleVelocity, 10, 255, 255, 0, 20.0f);
            break;
        case 'r':
            cout << "Very heavy bullet" << endl;
            if(mode != Default) clearParticles();
            mode = Default;
            currentParticle = Particle(particleVelocity, 100, 255, 255, 255, 40.0f);
            break;
        case 't':
            simPause = false;
            cout << "Custom bullet \n""Please enter the parameters \n" << endl;
            cout << "Mass: ";
            cin >> mass;
            cout << "Gravity: ";
            cin >> gravity;
            if(mode != Default) clearParticles();
            mode = Default;
            currentParticle = Particle(particleVelocity, mass, gravity);
            break;
        case 'b':
            SetupBlobGame();
            break;
        case 'l':
            cout << "Particles: " << tabParticle.size() << endl;
            break;
        case 'h':
            enableSpring = !enableSpring;
            cout << (enableSpring ? "Spring enabled" : "Spring disabled") << endl;
            break;
        case 'j':
            enableGravity = !enableGravity;
            cout << (enableGravity ? "Gravity enabled" : "Gravity disabled") << endl;
            break;
        case 'k':
            enableFriction = !enableFriction;
            cout << (enableFriction ? "Friction enabled" : "Friction disabled") << endl;
            break;
        case 'q':
            cout << "Wire" << endl;
            mode = Wire;
            enableDemo = true;
            clearParticles();
            tabParticle.emplace_back(new Particle(Vector(-100,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.emplace_back(new Particle(Vector(0,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.front()->position = Vector(ofGetWidth() / 2 -100, ofGetHeight() / 2, 0);
            tabParticle.back()->position = Vector(ofGetWidth() / 2 +100, ofGetHeight() / 2, 0);
            break;
        case 's':
            cout << "Rod" << endl;
            mode = Rod;
            enableDemo = true;
            clearParticles();
            tabParticle.emplace_back(new Particle(Vector(-100,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.emplace_back(new Particle(Vector(0,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.front()->position = Vector(ofGetWidth() / 2 -100, ofGetHeight() / 2, 0);
            tabParticle.back()->position = Vector(ofGetWidth() / 2 +100, ofGetHeight() / 2, 0);
            break;
        case 'c':
            cout << "Point Spring" << endl;
            mode = StaticSpring;
            enableDemo = true;
            clearParticles();
            tabParticle.emplace_back(new Particle(Vector(0,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.front()->position = Vector(ofGetWidth() / 2, ofGetHeight() / 2 - 100, 0);
            break;
        case 'f':
            cout << "Particle Spring" << endl;
            mode = DynamicSpring;
            enableDemo = true;
            clearParticles();
            tabParticle.emplace_back(new Particle(Vector(-100,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.emplace_back(new Particle(Vector(0,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.front()->position = Vector(ofGetWidth() / 2 -100, ofGetHeight() / 2, 0);
            tabParticle.back()->position = Vector(ofGetWidth() / 2 +100, ofGetHeight() / 2, 0);
            break;
        case 'g':
            cout << "Point Elastic" << endl;
            mode = StaticElastic;
            enableDemo = true;
            clearParticles();
            tabParticle.emplace_back(new Particle(Vector(0,0,0), 1, 255, 255, 255, 15.0f));
            tabParticle.front()->position = Vector(ofGetWidth() / 2 , ofGetHeight() / 2, 0);
            break;
        case 'x':
            cout << "Particle Elastic" << endl;
            mode = DynamicElastic;
            enableDemo = true;
            clearParticles();
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
