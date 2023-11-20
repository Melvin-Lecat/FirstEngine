#include "ofApp.h"

#include "Cone.h"
#include "FrictionGenerator.h"
#include "GravityGenerator.h"
#include "MatrixTest.h"
#include "QuaternionTest.h"
#include "VectorTest.h"


# define VP_STEP 50
# define VP_SIZE 500
#define MIN_FORCE -200.0f
#define MAX_FORCE 200.0f

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
    AddMultiLineText(helpPanel, helpLines, manualText);


    controlPanel.setup("Control Buttons");
    controlPanel.setPosition(glm::vec3(0,ofGetHeight()/2,0));
    gamePaused.setup("PauseGame");
    gamePaused.addListener(this,&ofApp::TogglePause);
    showHelp.setup("Enable Help window", false);
    showDebug.setup("Enable debug window", false);
    showAxis.setup("Show Grid/Axis", false);
    showForceAdd.setup("Add force", false);
    showObjectAdd.setup("Add object", false);
    controlPanel.add(&gamePaused);
    controlPanel.add(&showHelp);
    controlPanel.add(&showDebug);
    controlPanel.add(&showAxis);
    controlPanel.add(&showForceAdd);
    controlPanel.add(&showObjectAdd);
    fullscreenButton.setup("Fullscreen");
    fullscreenButton.addListener(this, &ofApp::Fullscreen);
    controlPanel.add(&fullscreenButton);
    controlPanel.add(clearAll.setup("Clear all objects"));

    debugPanel.setup("Object Details");
    debugPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    debugPanel.setPosition(glm::vec3(ofGetWidth()/3,0,0));
    
    debugPanel.add(position.setup("Position",""));
    AddMultiLineText(debugPanel, debugLines1, object.position.to_string());
    debugPanel.add(velocity.setup("Velocity",""));
    AddMultiLineText(debugPanel, debugLines2, object.linearVelocity.to_string());


    forcePanel.setup("Add Force");
    forcePanel.setSize(ofGetWidth() / 4, ofGetHeight());
    forcePanel.setPosition(glm::vec3(0,0,0));
    forcePanel.add(positionForceLabel.setup("Position Force", ""));
    forcePanel.add(xpInput.setup("X", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(ypInput.setup("Y", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(zpInput.setup("Z", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(velocityForceLabel.setup("Velocity Force", ""));
    forcePanel.add(xvInput.setup("X", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(yvInput.setup("Y", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(zvInput.setup("Z", 0, -MAX_FORCE, MAX_FORCE));
    launch.setup("Launch");
    launch.addListener(this,&ofApp::LaunchObject);
    forcePanel.add(&launch);

    objectPanel.setup("Add Object");
    objectPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    objectPanel.setPosition(glm::vec3(0,0,0));
    objectPanel.add(cdmObjectLabel.setup("Mass center position", ""));
    objectPanel.add(xpInputObject.setup("X", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(ypInputObject.setup("Y", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(zpInputObject.setup("Z", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(objectTypeLabel.setup("Object Type", ""));
    boxButton.setup("Box");
    coneButton.setup("Cone");
    addButton.setup("Add");
    objectPanel.add(&boxButton);
    objectPanel.add(&coneButton);
    objectPanel.add(&addButton);
    boxButton.addListener(this, &ofApp::setBoxType);
    coneButton.addListener(this, &ofApp::setConeType);
    addButton.addListener(this, &ofApp::AddObject);
    
    
}
void ofApp::setBoxType()
{
    objectType = BOX;
}

void ofApp::setConeType()
{
    objectType = CONE;   
}

void ofApp::AddObject()
{
    if (objectType == BOX)
    {
        Box obj = Box(20,20,20,Vector(xpInputObject, ypInputObject, zpInputObject));
        tabShape.emplace_back(obj);
    }
    else
    {
        // Cone obj = Cone(20,20,Vector(xpInputObject, ypInputObject, zpInputObject));
        //tabShape.emplace_back(obj);
    }
}


void ofApp::Fullscreen()
{
    ofToggleFullscreen();
}

void ofApp::TogglePause()
{
    showForceAdd = !showForceAdd;
}

void ofApp::LaunchObject()
{
    simPause = false;
    showForceAdd = false;
}

void ofApp::AddMultiLineText(ofxPanel& panel,std::vector<ofxLabel*> &lines, const std::string& text)
{
    auto textLines = ofSplitString(text, "\n");
    lines = std::vector<ofxLabel*>(textLines.size());
    for (int i=0; i<textLines.size(); i++)
    {
        lines[i] = new ofxLabel();
        lines[i]->setup(std::to_string(i),textLines[i]);
        panel.add(lines[i]);
    }
}
void updateLines(std::vector<ofxLabel*>& lines,const std::string &text)
{
    auto textSplit = ofSplitString(text, "\n");
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
    
    simPause = showForceAdd;
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
    
    if (!showAxis) ofDrawGrid(VP_STEP, VP_SIZE / VP_STEP, !showAxis, !showAxis, !showAxis, !showAxis);
    else ofDrawAxis(1000000);   

    ofDisableDepthTest();
    if(showDebug)
    {
        if (object.linearVelocity.magnitude() > 2)
        {
            ofSetColor(ofColor::greenYellow);
            ofDrawArrow(object.position.v3(), (object.position + object.linearVelocity).v3(), 10);
            ofSetColor(ofColor::white);
        }
        
    }
    

    cam.end();
    drawInteractionArea();
    ofSetColor(255);

    controlPanel.draw();
    if (showHelp) helpPanel.draw();
    if(showForceAdd) forcePanel.draw();
    if(showObjectAdd) objectPanel.draw();
    if (showDebug)
    {
        debugPanel.draw();
        updateLines(debugLines1,object.position.to_string());
        updateLines(debugLines2,object.linearVelocity.to_string());
    }
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
