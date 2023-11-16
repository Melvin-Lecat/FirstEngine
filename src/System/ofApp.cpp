#include "ofApp.h"

#include "Forces/ParticleGravity.h"
#include "Tests/VectorTest.h"

# define VP_STEP 50
# define VP_SIZE 500


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
    
    boxObject.addForce(Vector(0,20,0));
}

void ofApp::checkBoundaries()
{
    for(auto box: tabBox)
    {
        // Check X borders
        if (abs(box.position.x )> VP_SIZE)
            box.linearVelocity *= -1;

        // Check Y borders
        if (abs(box.position.y) > VP_SIZE)
            box.linearVelocity *= -1;

        // Check Z borders
        if (abs(box.position.z) > VP_SIZE)
            box.linearVelocity *= -1;

    }

    auto box = &boxObject;
    if (abs(box->position.x) > VP_SIZE)
        box->linearVelocity *= -1;

    // Check Y borders
    if (abs(box->position.y) > VP_SIZE)
        box->linearVelocity *= -1;

    // Check Z borders
    if (abs(box->position.z) > VP_SIZE)
        box->linearVelocity *= -1;

}

void ofApp::updateForces()
{
    {
        ParticleGravity pg(Vector(0, -9.81, 0));
        // Appliquer les forces

    }
    particleForceRegistry.updateForces(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    checkBoundaries();
    if (simPause) return;
    // Set the delta time using the last frame time
    updateForces();
    // Todo à modifier pour implémenter des gameobjects
    boxObject.eulerIntegration(ofGetLastFrameTime());
    
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
    ofBackground(20);
    cam.begin();
    ofEnableDepthTest();

    boxObject.shape.setOrientation(boxObject.orientation.q());
    boxObject.shape.setPosition(boxObject.position.v3());
    boxObject.shape.draw();
    
    ofDrawGrid(VP_STEP, VP_SIZE/VP_STEP, false, showAxis, showAxis, showAxis);
    ofDisableDepthTest();
    
    cam.end();
    drawInteractionArea();
    ofSetColor(255);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case ' ':
        cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
        break;
    case 'a':
    case 'A':
        showAxis = !showAxis;
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
    // todo en 3D
    switch (button)
    {
    case OF_MOUSE_BUTTON_LEFT:

        break;
    case OF_MOUSE_BUTTON_RIGHT:

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
