#include "ofApp.h"
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

//--------------------------------------------------------------
void ofApp::update()
{
    checkUnboundParticules();
    if (simPause) return;
    // Set the delta time using the last frame time
    updateParticles(tabParticle, ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Drawing the cursor for initial velocity
    Vector cursor = Vector(velocity.x, ofGetHeight() - velocity.y);
    ofDrawLine(Vector(0, ofGetHeight()).v2(), cursor.v2());
    // Drawing the particles
    for (Particle* p : tabParticle)
    {
        ofSetColor(p->color[0], p->color[1], p->color[2]);
        Vector realPos = Vector(p->position.x, ofGetHeight() - p->position.y);
        ofDrawCircle(realPos.v2(), RAD);
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
        currentParticle = Particle(velocity, 1, 9.81f); 
        break;
    case 'z':
        cout << "Laser" << endl;
        currentParticle = Particle(velocity, 2, 0, 255, 0, 0); 
        break;
    case 'e':
        cout << "Heavy bullet" << endl;
        currentParticle = Particle(velocity, 3, 50.0f);  
        break;
    case 'r':
        cout << "Very heavy bullet" << endl;
        currentParticle = Particle(velocity, 4, 100.0f); 
        break;
    case 't':
        simPause = false;
        cout << "Custom bullet \n""Please enter the parameters \n" << endl;
        cout << "Mass: ";
        cin >> mass;
        cout << "Gravity: ";
        cin >> gravity;
        currentParticle = Particle(velocity, mass, gravity);
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
    velocity = Vector(x, glm::abs(ofGetHeight() - y));
    currentParticle.velocity = velocity;
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