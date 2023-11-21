#include "ofApp.h"

#include "Cone.h"
#include "FrictionGenerator.h"
#include "GravityGenerator.h"
#include "MatrixTest.h"
#include "QuaternionTest.h"
#include "VectorTest.h"


# define VP_STEP 50
# define VP_SIZE 500
# define MAX_FORCE 1000.0f

// Width is the X axis
# define BOX_WIDTH 20
// Heigth is the Y axis
# define BOX_HEIGHT 10
// Lenght is the Z axis
# define BOX_LENGHT 100

// Radius is the X and Z axis
# define CONE_RADIUS 200
# define CONE_HEIGHT 50

float maxX = max(BOX_WIDTH, CONE_RADIUS);
float maxY = max(BOX_HEIGHT, CONE_HEIGHT);
float maxZ = max(BOX_LENGHT, CONE_RADIUS);

bool bHelpText;

void ofApp::setupForcePanel()
{
    forcePanel.setup("Add Force");
    forcePanel.setSize(ofGetWidth() / 4, ofGetHeight());
    forcePanel.setPosition(glm::vec3(0,0,0));
    
    forcePanel.add(positionForceLabel.setup("Force Position", ""));
    forcePanel.add(xpInput.setup("X", 0, -maxX, maxX));
    forcePanel.add(ypInput.setup("Y", 0, -maxY, maxY));
    forcePanel.add(zpInput.setup("Z", 0, -maxZ, maxZ));
    
    forcePanel.add(intensityForceLabel.setup("Force Intensity", ""));
    forcePanel.add(xvInput.setup("IX", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(yvInput.setup("IY", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(zvInput.setup("IZ", 0, -MAX_FORCE, MAX_FORCE));
    
    launch.setup("Launch");
    launch.addListener(this,&ofApp::launchObject);
    forcePanel.add(&launch);
}

void ofApp::setupDebugPanel()
{
    debugPanel.setup("Object Details");
    debugPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    debugPanel.setPosition(glm::vec3(ofGetWidth()/3,0,0));
    Shape object; 
    debugPanel.add(position.setup("Position",""));
    addMultiLineText(debugPanel, debugLines1, object.position.to_string());
    debugPanel.add(velocity.setup("Velocity",""));
    addMultiLineText(debugPanel, debugLines2, object.linearVelocity.to_string());
}

void ofApp::setupObjectPanel()
{
    // Panel setup 
    objectPanel.setup("Add Object");
    objectPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    objectPanel.setPosition(glm::vec3(0,0,0));

    //Object type
    objectPanel.add(objectTypeLabel.setup("Object Type", ""));
    boxButton.setup("Box");
    objectPanel.add(&boxButton);
    boxButton.addListener(this, &ofApp::setBoxType);
    coneButton.setup("Cone");
    objectPanel.add(&coneButton);
    coneButton.addListener(this, &ofApp::setConeType);

    //Object center position
    objectPanel.add(cdmObjectLabel.setup("Mass center position", ""));
    objectPanel.add(xpInputObject.setup("XP", 0, -maxX, maxX));
    objectPanel.add(ypInputObject.setup("YP", 0, -maxY, maxY));
    objectPanel.add(zpInputObject.setup("ZP", 0, -maxZ, maxZ));

    //Object initial Force
    objectPanel.add(initialForceLabel.setup("Initial Force Applied",""));
    objectPanel.add(xfInput.setup("XF", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(yfInput.setup("YF", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(zfInput.setup("ZF", 0, -MAX_FORCE, MAX_FORCE));

    // Submit object
    addButton.setup("Add");
    addButton.addListener(this, &ofApp::addObject);
    objectPanel.add(&addButton);
}

void ofApp::setupControlPanel()
{
    controlPanel.setup("Control Buttons");
    controlPanel.setPosition(glm::vec3(0,ofGetHeight()/2,0));
    gamePaused.setup("PauseGame");
    gamePaused.addListener(this,&ofApp::togglePause);
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
    fullscreenButton.addListener(this, &ofApp::fullscreen);
    controlPanel.add(&fullscreenButton);
    controlPanel.add(clearAll.setup("Clear all objects"));
    clearAll.addListener(this, &ofApp::clearAllObjects);
}
void ofApp::setupHelpPanel()
{
    helpPanel.setup("User Manual:");
    helpPanel.setSize(ofGetWidth() / 2, ofGetHeight());
    addMultiLineText(helpPanel, helpLines, manualText);
}

//--------------------------------------------------------------
void ofApp::setup()
{
    // Run the unit tests
    unitTests();

    // Set the color of the items
    ofSetColor(255, 255, 255);

    ofSetVerticalSync(true);
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();
    ofSetCircleResolution(64);
    bHelpText = true;

    // Setup the GUI
    setupControlPanel();
    setupHelpPanel();
    setupDebugPanel();
    setupForcePanel();
    setupObjectPanel();
    
}
void ofApp::setBoxType()
{
    objectType = BOX;
}

void ofApp::setConeType()
{
    objectType = CONE;   
}

void ofApp::addObject()
{
    switch (objectType)
    {
        case BOX:
            tabShape.emplace_back(new Box(BOX_WIDTH,BOX_HEIGHT,BOX_LENGHT,Vector(xpInputObject, ypInputObject, zpInputObject)));
            break;
        case CONE:
            tabShape.emplace_back(new Cone(CONE_RADIUS,CONE_HEIGHT,Vector(xpInputObject, ypInputObject, zpInputObject)));
            break;
    }
    tabShape.back()-> addForce(Vector(xfInput, yfInput, zfInput));
}

void ofApp::clearAllObjects()
{
    for (Shape* obj : tabShape)
    {
        delete obj;
    }
    tabShape.clear();
}

void ofApp::fullscreen()
{
    ofToggleFullscreen();
}

void ofApp::togglePause()
{
    showForceAdd = !showForceAdd;
    showForceAdd = !showForceAdd;
}

void ofApp::launchObject()
{
    addForceObject(*(tabShape.back()),Vector(xvInput,yvInput,zvInput),Vector(xpInput,ypInput,zpInput));
    simPause = false;
    showForceAdd = false;
}

void ofApp::addMultiLineText(ofxPanel& panel,std::vector<ofxLabel*> &lines, const std::string& text)
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
        if (glm::abs(box->position.x) > VP_SIZE)
        {
            box->position.x = glm::sign(box->position.x) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity *= -1;
        }

        // Check Y borders
        if (abs(box->position.y) > VP_SIZE)
        {
            box->position.y = glm::sign(box->position.y) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity *= -1;
        }

        // Check Z borders
        if (abs(box->position.z) > VP_SIZE)
        {
            box->position.z = glm::sign(box->position.z) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity *= -1;
        }
    }
}

void ofApp::updateForces()
{
    {
        GravityGenerator genGravity(Vector(0, -9.81, 0));
        FrictionGenerator genFriction(0.1);
        // Appliquer les forces
        for (auto& object : tabShape)
        {
            //forceRegistry.add(object, &genGravity);
            //forceRegistry.add(object, &genFriction);
        }
    }
    forceRegistry.updateForces(delta_t);
}

Vector force;

void ofApp::addForceObject(Shape& obj, Vector forceIntensity, Vector pointApplication)
{
    
    obj.addForce(forceIntensity, pointApplication);
}

//--------------------------------------------------------------
void ofApp::update()
{
    delta_t = static_cast<float>(ofGetLastFrameTime()) * simSpeed;
    checkBoundaries();
    
    simPause = showForceAdd;
    if (simPause) return;
    // Set the delta time using the last frame time
    updateForces();
    for(auto object : tabShape)
    {
        object->eulerIntegration(delta_t);
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
    ofBackground(20);
    cam.begin();
    ofEnableDepthTest();

    for (auto& object : tabShape)
    {
        object->draw();
    }
    
    if (!showAxis) ofDrawGrid(VP_STEP, VP_SIZE / VP_STEP, !showAxis, !showAxis, !showAxis, !showAxis);
    else ofDrawAxis(1000000);   
    ofDisableDepthTest();
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
        auto object = tabShape.back();
        updateLines(debugLines1,object->position.to_string());
        updateLines(debugLines2,object->linearVelocity.to_string());
    }
    if(showDebug)
    {
        
        auto object = tabShape.back();
        if (object->linearVelocity.magnitude() > 2)
        {
            ofSetColor(ofColor::greenYellow);
            ofDrawArrow(object->position.v3(), (object->position + object->linearVelocity).v3(), 10);
            ofSetColor(ofColor::white);
        }
        
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
