#include "ofApp.h"

#include "Forces/ParticleGravity.h"
#include "Forces/FixedSpringGenerator.h"
#include "Forces/ParticleFriction.h"
#include "Objects/CollisionManager2D.h"
#include "Tests/VectorTest.h"
#define RAD 15


bool bHelpText;

//--------------------------------------------------------------
void ofApp::setup()
{
    // Run the unit tests
    unitTests();

    // Set the color of the items
    ofSetColor(255, 255, 255);
    // Present the user manual
    // TODO: => UI temporaire 
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
    boxObject.position = Vector(0, 0, 0);
    ofSetVerticalSync(true);

    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    ofSetCircleResolution(64);
    bHelpText = true;
}

/**
 * @brief Check if the particles are out of the screen and delete them
 * 
 */
void ofApp::checkUnboundParticles()
{
    // Iterates over the list of particles
    for (auto particle = tabParticle.begin(); particle != tabParticle.end();)
    {
        // Check if the particle is out of the screen
        if ((*particle)->position.y < -(*particle)->radius || (*particle)->position.x > static_cast<float>(ofGetWidth())
            + (*particle)->radius)
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


void ofApp::checkBoundaries()
{
    float f = -1;
    for (auto p : tabParticle)
    {
        if (p->position.x < p->radius)
        {
            p->velocity.x *= f;
        }
        if (p->position.x > ofGetWidth() - p->radius)
        {
            p->velocity.x *= f;
        }
        if (p->position.y < p->radius)
        {
            p->velocity.y *= f;
        }
        if (p->position.y > ofGetHeight() - p->radius)
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
            particleForceRegistry.add(p, &pf);
        }
    }
    else
    {
        for (auto p = tabParticle.begin(); p != tabParticle.end(); ++p)
        {
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
    CollisionManager2D::CheckCollision(tabParticle);
    checkBoundaries();
    if (simPause) return;
    // Set the delta time using the last frame time
    updateForces();
    updateParticles(tabParticle, ofGetLastFrameTime());
    boxObject.addForce(Vector(0,10,0), Vector(1,1,1));
    boxObject.eulerIntegration(ofGetLastFrameTime());
    boxObject.shape.setOrientation(boxObject.orientation.q());
    camera.lookAt(boxObject.position.v3());
}

void ofApp::DrawParticle(Particle p)
{
    ofSetColor(p.color[0], p.color[1], p.color[2]);
    auto realPos = Vector(p.position.x, ofGetHeight() - p.position.y);
    ofDrawCircle(realPos.v2(), p.radius);
    ofSetColor(255, 255, 255);
}

void ofApp::DrawSystem()
{
    ofSetColor(OF_CONSOLE_COLOR_YELLOW);
    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, RAD);
    // Drawing the cursor for initial velocity
    auto tempOrigin = Vector(particleOrigin.x, ofGetHeight() - particleOrigin.y);
    auto tempVelocity = Vector(particleVelocity.x, ofGetHeight() - particleVelocity.y);
    ofSetColor(OF_CONSOLE_COLOR_GREEN);
    ofDrawCircle(tempOrigin.v2(), RAD / 2);
    ofSetColor(255, 255, 255);
    ofDrawLine(tempOrigin.v2(), tempVelocity.v2());
}

void ofApp::DrawParticles()
{
    if (blobgame)
    {
        mainParticle.draw();
        //DrawParticle(mainParticle);
    }
    // Drawing the particles
    for (Particle* p : tabParticle)
    {
        p->updateColor();
        p->draw();
        //DrawParticle(*p);
    }
}

void ofApp::drawInteractionArea()
{
    ofRectangle vp = ofGetCurrentViewport();
    float r = std::min<float>(vp.width, vp.height) * 0.5f;
    float x = vp.width * 0.5f;
    float y = vp.height * 0.5f;

    ofPushStyle();
    ofSetLineWidth(3);
    ofSetColor(255, 255, 0);
    ofNoFill();
    glDepthMask(false);
    ofDrawCircle(x, y, r);
    glDepthMask(true);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    /*camera.setGlobalPosition({ 0,0,0 });
    camera.begin();
    camera.lookAt(boxObject.position.v3());
    DrawSystem();
    DrawParticles();
    //boxObject.setPosition(Vector(ofGetWidth() / 2, ofGetHeight() / 2,0));

    camera.end();*/

    ofBackground(20);
    cam.begin();
    ofEnableDepthTest();

    boxObject.setPosition(Vector(0, 0, 0));
    boxObject.shape.setOrientation(boxObject.orientation.q());
    boxObject.shape.draw();

    box.setPosition(0, 0, 0);
    box.set(boxObject.getWidth(), boxObject.getHeight(), boxObject.getDepth());
    box.setOrientation(boxObject.orientation.q());

    box.draw();


    ofDrawGrid(200, 10, true, true, true, true);
    ofDisableDepthTest();


    cam.end();
    drawInteractionArea();
    ofSetColor(255);
}

// TODO: A archiver
void ofApp::SetupBlobGame()
{
    auto positioncentre = Vector(ofGetWidth() / 2, ofGetHeight() / 2);
    auto blobdroite = Vector(60, 0);
    auto blobgauche = Vector(-60, 0);
    auto blobhaut = Vector(0, 60);
    auto blobbas = Vector(0, -60);

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
        /*case 'a':
            cout << "Standard bullet" << endl;
            currentParticle = Particle(particleVelocity, 1, 10.0f);
            break;
        case 'z':
            cout << "Laser" << endl;
            currentParticle = Particle(particleVelocity, 0.5, 0, 255, 0, 2);
            break;
        case 'e':
            cout << "Heavy bullet" << endl;
            currentParticle = Particle(particleVelocity, 10, 255, 255, 0, 20.0f);
            break;*/
        case 'r':
            cout << "Very heavy bullet" << endl;
            currentParticle = Particle(particleVelocity, 100, 255, 255, 255, 40.0f);
            break;
        case 't':
            simPause = false;
            cout << "Custom bullet \n""Please enter the parameters \n" << endl;
            cout << "Mass: ";
            cin >> mass;
            cout << "Gravity: ";
            cin >> gravity;
            currentParticle = Particle(particleVelocity, mass);
            break;
        case 'b':
            SetupBlobGame();
            break;
        case 'l':
            cout << "Particles: " << tabParticle.size() << endl;
            break;
        case 'z':
            cout << "Expected position: " << camera.getPosition() + Vector(0, ofGetLastFrameTime(), 0).v3() << endl;
            camera.setPosition(camera.getPosition() + Vector(0, ofGetLastFrameTime(), 0).v3());
            cout << "Camera position: " << camera.getPosition() << endl;
            break;
        case 's':
            camera.setPosition(camera.getPosition() + Vector(0, -ofGetLastFrameTime(), 0).v3());
            break;
        case 'q':
            camera.setPosition(camera.getPosition() + Vector(-ofGetLastFrameTime(), 0, 0).v3());
            break;
        case 'd':
            camera.setPosition(camera.getPosition() + Vector(ofGetLastFrameTime(), 0, 0).v3());
            break;
        case 'a':
            camera.setPosition(camera.getPosition() + Vector(0, 0, -ofGetLastFrameTime()).v3());
            break;
        case 'e':
            camera.setPosition(camera.getPosition() + Vector(0, 0, ofGetLastFrameTime()).v3());
            break;
        default:
            break;
        }
    }
    switch (key)
    {
    case ' ':
        cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
        break;
    case 'C':
    case 'c':
        cam.getMouseInputEnabled() ? cam.disableMouseInput() : cam.enableMouseInput();
        break;
    case 'F':
    case 'f':
        ofToggleFullscreen();
        break;
    case 'H':
    case 'h':
        bHelpText ^= true;
        break;
    case 'I':
    case 'i':
        cam.getInertiaEnabled() ? cam.disableInertia() : cam.enableInertia();
        break;
    case 'Y':
    case 'y':
        cam.setRelativeYAxis(!cam.getRelativeYAxis());
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

/////////////////////////////// UNIT TESTS ///////////////////////////////

/**
 * @brief Run the unit tests, show nothing if all tests are passed
 * 
 */
void ofApp::unitTests()
{
    vectorTests();
}

void ofApp::vectorTests()
{
    VectorTest vectorTest;

    vectorTest.testScalarProduct();
    vectorTest.testVectorialProduct();
    vectorTest.testProjection();
}
