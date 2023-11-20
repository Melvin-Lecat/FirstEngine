#include "ofApp.h"

#include "FrictionGenerator.h"
#include "GravityGenerator.h"
#include "MatrixTest.h"
#include "QuaternionTest.h"
#include "VectorTest.h"


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
    object.position = Vector(0, 0, 0);
    //object.moveCenterMass(Vector(10,0,0));
    ofSetVerticalSync(true);

    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    ofSetCircleResolution(64);
    bHelpText = true;
    tabShape.emplace_back(object);

    // Setup the GUI
    helpPanel.setup("User Manual:");
    helpPanel.setSize(ofGetWidth() / 2, ofGetHeight());
    AddMultiLineText(helpPanel, helpLines, multilineText);


    controlPanel.setup("Control Buttons");
    controlPanel.setPosition(glm::vec3(0,ofGetHeight()/2,0));
    gamePaused.setup("PauseGame");
    gamePaused.addListener(this,&ofApp::TogglePause);
    controlPanel.add(&gamePaused);

    
    debugPanel.setup("Object Details");
    debugPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    debugPanel.setPosition(glm::vec3(ofGetWidth()/3,0,0));
    
    debugPanel.add(position.setup("Position",""));
    AddMultiLineText(debugPanel, debugLines1, object.position.to_string());
    debugPanel.add(velocity.setup("Velocity",""));
    AddMultiLineText(debugPanel, debugLines2, object.linearVelocity.to_string());

}
void ofApp::TogglePause()
{
    simPause = !simPause;
}

void ofApp::AddMultiLineText(ofxPanel& _panel,std::vector<ofxLabel*> &_lines, const std::string& _text)
{
    auto textLines = ofSplitString(_text, "\n");
    _lines = std::vector<ofxLabel*>(textLines.size());
    for (int i=0; i<textLines.size(); i++)
    {
        _lines[i] = new ofxLabel();
        _lines[i]->setup(std::to_string(i),textLines[i]);
        _panel.add(_lines[i]);
    }
}
void updateLines(std::vector<ofxLabel*>& lines,const std::string &_text)
{
    auto textSplit = ofSplitString(_text, "\n");
    for (int i=0; i<lines.size(); i++)
    {
        lines[i]->setup("",textSplit[i]);
    }
}
void ofApp::checkBoundaries()
{
    for (auto box : tabShape)
    {
        // Check X borders
        if (glm::abs(box.position.x) > VP_SIZE)
        {
            box.position.x = glm::sign(box.position.x) > 0 ? VP_SIZE : -VP_SIZE;
            box.linearVelocity *= -1;
        }

        // Check Y borders
        if (abs(box.position.y) > VP_SIZE)
        {
            box.position.y = glm::sign(box.position.y) > 0 ? VP_SIZE : -VP_SIZE;
            box.linearVelocity *= -1;
        }

        // Check Z borders
        if (abs(box.position.z) > VP_SIZE)
        {
            box.position.z = glm::sign(box.position.z) > 0 ? VP_SIZE : -VP_SIZE;
            box.linearVelocity *= -1;
        }
    }


    // Check X borders
    if (abs(object.position.x) >= VP_SIZE)
    {
        object.position.x = glm::sign(object.position.x) > 0 ? VP_SIZE : -VP_SIZE;
        object.linearVelocity.x *= -1;
    }


    // Check Y borders
    if (abs(object.position.y) >= VP_SIZE)
    {
        object.position.y = glm::sign(object.position.y) > 0 ? VP_SIZE : -VP_SIZE;
        object.linearVelocity.y *= -1;
    }

    // Check Z borders
    if (abs(object.position.z) >= VP_SIZE)
    {
        object.position.z = glm::sign(object.position.z) > 0 ? VP_SIZE : -VP_SIZE;
        object.linearVelocity.z *= -1;
    }
}

void ofApp::updateForces()
{
    {
        GravityGenerator genGravity(Vector(0, -9.81, 0));
        FrictionGenerator genFriction(0.1);
        // Appliquer les forces
        forceRegistry.add(&object, &genGravity);
        forceRegistry.add(&object, &genFriction);
    }
    forceRegistry.updateForces(delta_t);
}

Vector force;

void ofApp::addForceObject(Shape& obj, Vector forceIntensity, Vector pointApplication)
{
    
    (obj).addForce(forceIntensity, pointApplication);
}

//--------------------------------------------------------------
void ofApp::update()
{
    delta_t = static_cast<float>(ofGetLastFrameTime()) * simSpeed;
    checkBoundaries();
    if (simPause) return;
    // Set the delta time using the last frame time
    updateForces(); // Todo à modifier pour implémenter des gameobjects
    static int i = 0;
    static bool b = false;
    i++;
    if (i == 3)
    {
        b = true;
    }
    force = Vector(20, 0, 30);
    if (!b) addForceObject(object, force, Vector(10, 10, 10));
    object.eulerIntegration(delta_t);
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

    object.draw();

    //ofDrawAxis(1000000);  
    ofDrawGrid(VP_STEP, VP_SIZE / VP_STEP, true, showAxis, showAxis, showAxis);
    ofDisableDepthTest();
    if (object.linearVelocity.magnitude() > 2)
    {
        ofSetColor(ofColor::greenYellow);
        ofDrawArrow(object.position.v3(), (object.position + object.linearVelocity).v3(), 10);
        ofSetColor(ofColor::white);
    }

    cam.end();
    drawInteractionArea();
    ofSetColor(255);

    helpPanel.draw();
    controlPanel.draw();
    debugPanel.draw();
    updateLines(debugLines1,object.position.to_string());
    updateLines(debugLines2,object.linearVelocity.to_string());
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
    static bool isFirst = true;
    auto pos = cam.screenToWorld(ofVec3f(x, y, 0));
    // Setting the initial velocity with the mouse position
    // todo en 3D
    switch (button)
    {
    case OF_MOUSE_BUTTON_LEFT:
        break;
    case OF_MOUSE_BUTTON_RIGHT:
        if (isFirst)
        {
            firstP = Vector(pos.x, pos.y, pos.z);
            drawLine = false;
        }
        else
        {
            secP = Vector(pos.x, pos.y, pos.z);
            drawLine = true;
        }

        isFirst = !isFirst;
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
    matrixTests();
    quaternionTests();
}

void ofApp::vectorTests()
{
    VectorTest vectorTest;

    vectorTest.testScalarProduct();
    vectorTest.testVectorialProduct();
    vectorTest.testProjection();
}

void ofApp::matrixTests()
{
    MatrixTest matrixTest;

    matrixTest.testMatrixAddition();
    matrixTest.testMatrixSubtraction();
    matrixTest.testMatrixMultiplication();
    matrixTest.testMatrixMultiplicationByScalar();
    matrixTest.testMatrixInverse();

    matrixTest.testMatrix4x4Addition();
    matrixTest.testMatrix4x4Subtraction();
    matrixTest.testMatrix4x4Multiplication();
    matrixTest.testMatrix4x4MultiplicationByScalar();
}

void ofApp::quaternionTests()
{
    QuaternionTest quaternionTest;

    quaternionTest.testQuaternionAddition();
    quaternionTest.testQuaternionMultiplication();
    quaternionTest.testQuaternionMultiplicationByScalar();
    quaternionTest.testQuaternionDivision();

    quaternionTest.testQuaternionDifference();
    quaternionTest.testQuaternionNormalize();
    quaternionTest.testQuaternionInverse();
    quaternionTest.testQuaternionScalarProduct();
    quaternionTest.testQuaternionApplyRotation();
    quaternionTest.testQuaternionToMatrix();
}
