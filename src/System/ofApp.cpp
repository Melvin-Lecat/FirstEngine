#include "ofApp.h"

#include "CollisionManager.h"


float maxX = max(BOX_WIDTH, CONE_RADIUS);
float maxY = max(BOX_HEIGTH, CONE_HEIGHT);
float maxZ = max(BOX_LENGTH, CONE_RADIUS);

bool bHelpText;

/**
 * @brief Setup the force panel
 * 
 */
void ofApp::setupForcePanel()
{
    forcePanel.setup("Add Force");
    forcePanel.setSize(ofGetWidth() / 4, ofGetHeight());
    forcePanel.setPosition(glm::vec3(0, 0, 0));

    forcePanel.add(positionForceLabel.setup("Force Position", ""));
    forcePanel.add(xpInput.setup("X", 0, -maxX, maxX));
    forcePanel.add(ypInput.setup("Y", 0, -maxY, maxY));
    forcePanel.add(zpInput.setup("Z", 0, -maxZ, maxZ));

    forcePanel.add(intensityForceLabel.setup("Force Intensity", ""));
    forcePanel.add(xvInput.setup("IX", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(yvInput.setup("IY", 0, -MAX_FORCE, MAX_FORCE));
    forcePanel.add(zvInput.setup("IZ", 0, -MAX_FORCE, MAX_FORCE));

    launch.setup("Launch");
    launch.addListener(this, &ofApp::launchObject);
    forcePanel.add(&launch);
}

/**
 * @brief Setup the debug panel
 * 
 */
void ofApp::setupDebugPanel()
{
    debugPanel.setup("Object Details");
    debugPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    debugPanel.setPosition(glm::vec3(ofGetWidth() / 3, 0, 0));
    Shape object;
    debugPanel.add(position.setup("Position", ""));
    addMultiLineText(debugPanel, debugLines1, object.position.to_string());
    debugPanel.add(velocity.setup("Velocity", ""));
    addMultiLineText(debugPanel, debugLines2, object.linearVelocity.to_string());
}

/**
 * \brief Setup the object panel
 */
void ofApp::setupObjectPanel()
{
    // Panel setup 
    objectPanel.setup("Add Object");
    objectPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    objectPanel.setPosition(glm::vec3(ofGetWidth()*0.75, 0, 0));

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
    objectPanel.add(initialForceLabel.setup("Initial Force Applied", ""));
    objectPanel.add(xfInput.setup("XF", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(yfInput.setup("YF", 0, -MAX_FORCE, MAX_FORCE));
    objectPanel.add(zfInput.setup("ZF", 0, -MAX_FORCE, MAX_FORCE));

    // Submit object
    addButton.setup("Add");
    addButton.addListener(this, &ofApp::addObject);
    objectPanel.add(&addButton);
}

/**
 * @brief Setup the control panel
 * 
 */
void ofApp::setupControlPanel()
{
    controlPanel.setup("Control Buttons");
    controlPanel.setPosition(glm::vec3(0, ofGetHeight() / 2, 0));
    gamePaused.setup("PauseGame");
    gamePaused.addListener(this, &ofApp::togglePause);
    showHelp.setup("Enable Help window", false);
    showDebug.setup("Enable debug window", false);
    showAxis.setup("Show Grid/Axis", false);
    showForceAdd.setup("Add force", false);
    controlPanel.add(&gamePaused);
    controlPanel.add(&showHelp);
    controlPanel.add(&showDebug);
    controlPanel.add(&showAxis);
    controlPanel.add(&showForceAdd);
    fullscreenButton.setup("Fullscreen");
    fullscreenButton.addListener(this, &ofApp::fullscreen);
    controlPanel.add(&fullscreenButton);
    controlPanel.add(clearAll.setup("Clear all objects"));
    controlPanel.add(gravityToggle.setup("Enable gravity", false));
    controlPanel.add(frictionToggle.setup("Enable friction", false));
    controlPanel.add(collisionToggle.setup("Enable collisions", true));
    clearAll.addListener(this, &ofApp::clearAllObjects);
}

/**
 * \brief Setup the help panel
 */
void ofApp::setupHelpPanel()
{
    helpPanel.setup("User Manual:");
    helpPanel.setSize(ofGetWidth() / 2, ofGetHeight());
    addMultiLineText(helpPanel, helpLines, manualText);
}

/**
 * \brief  Setup the collision panel
 */
void ofApp::setupCollisionPanel()
{
    collisionPanel.setup("Collision Details");
    collisionPanel.setSize(ofGetWidth() / 4, ofGetHeight());
    collisionPanel.setPosition(glm::vec3(ofGetWidth() / 3, 0, 0));
    collisionPanel.add(broadCollisions.setup("Broad Collisions", ""));
    collisionPanel.add(narrowCollisions.setup("Narrow Collision", ""));
}

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
    setupCollisionPanel();
    
}

//--------------------------------------------------------------

/**
 * \brief Box button handler
 */
void ofApp::setBoxType()
{
    objectType = BOX;
}

/**
 * \brief Cone button handler
 */
void ofApp::setConeType()
{
    objectType = CONE;
}

/**
 * \brief Add button handler. Adds a new object to the scene configured by the UI
 */
void ofApp::addObject()
{
    Shape* s;
    switch (objectType)
    {
    case BOX:
        s = new Box(BOX_WIDTH,BOX_HEIGTH,BOX_LENGTH,
                                      Vector(xpInputObject, ypInputObject, zpInputObject));
        tabShape.emplace_back(s);
        octree.insert(s);
        break;
    case CONE:
        tabShape.emplace_back(new Cone(CONE_RADIUS,CONE_HEIGHT, Vector(xpInputObject, ypInputObject, zpInputObject)));
        break;
    }
    // We divide the force by delta_t to increase the applied force as it is meant to be an impulse
    tabShape.back()->addForce(Vector(xfInput, yfInput, zfInput)*(1/delta_t), Vector(0,0,0));
}

/**
 * \brief Clear all objects from the scene
 */
void ofApp::clearAllObjects()
{
    for (Shape* obj : tabShape)
    {
        delete obj;
    }
    tabShape.clear();
}

/**
 * \brief Fullscreen toggle handler
 */
void ofApp::fullscreen()
{
    ofToggleFullscreen();
}

/**
 * \brief Pause toggle handler
 */
void ofApp::togglePause()
{
    showForceAdd = !showForceAdd;
    showForceAdd = !showForceAdd;
}

/**
 * \brief Launch button handler
 */
void ofApp::launchObject()
{
    if (tabShape.empty()) std::cout << "No object to add force to !" << std::endl;
    else
    {
        addForceObject(*(tabShape.back()), Vector(xvInput, yvInput, zvInput), Vector(xpInput, ypInput, zpInput));
        simPause = false;
        showForceAdd = false;
    }
}

/**
 * \brief  Add multiple lines of text to a panel
 * \param panel The panel to add the lines to
 * \param lines The vector of lines to initialize
 * \param text The text to prompted
 */
void ofApp::addMultiLineText(ofxPanel& panel, std::vector<ofxLabel*>& lines, const std::string& text)
{
    auto textLines = ofSplitString(text, "\n");
    lines = std::vector<ofxLabel*>(textLines.size());
    for (int i = 0; i < textLines.size(); i++)
    {
        lines[i] = new ofxLabel();
        lines[i]->setup(std::to_string(i), textLines[i]);
        panel.add(lines[i]);
    }
}

/**
 * \brief Update the text of multiple lines of text
 * \param lines The vector of lines to update
 * \param text The text to prompted
 */
void updateLines(std::vector<ofxLabel*>& lines, const std::string& text)
{
    auto textSplit = ofSplitString(text, "\n");
    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->setup("", textSplit[i]);
    }
}
//--------------------------------------------------------------

/**
 * \brief Checks if the objects are out of bounds
 */
void ofApp::checkBoundaries()
{
    for (auto box : tabShape)
    {
        // Check X borders
        if (glm::abs(box->position.x) > VP_SIZE)
        {
            box->position.x = glm::sign(box->position.x) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity.x *= -1;
        }

        // Check Y borders
        if (abs(box->position.y) > VP_SIZE)
        {
            box->position.y = glm::sign(box->position.y) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity.y *= -1;
        }

        // Check Z borders
        if (abs(box->position.z) > VP_SIZE)
        {
            box->position.z = glm::sign(box->position.z) > 0 ? VP_SIZE : -VP_SIZE;
            box->linearVelocity.z *= -1;
        }
    }
}

GravityGenerator genGravity(Vector(0, -9.81, 0));
FrictionGenerator genFriction(0.1);

/**
 * \brief Update the forces applied to the objects
 */
void ofApp::updateForces()
{
    {
        // Appliquer les forces
        for (auto& object : tabShape)
        {
            if(gravityToggle) forceRegistry.add(object, &genGravity);
            if(frictionToggle) forceRegistry.add(object, &genFriction);
        }
    }
    forceRegistry.updateForces(delta_t);
}

Vector force;

/**
 * \brief Add a force to an object. Is used as a callback for the launch force button
 * \param obj The object to add the force to
 * \param forceIntensity The intensity of the force
 * \param pointApplication The point of application of the force
 */
void ofApp::addForceObject(Shape& obj, Vector forceIntensity, Vector pointApplication)
{
    obj.addForce(forceIntensity, pointApplication);
}

/**
 * \brief Handle the collision detection and resolve
 */
void ofApp::collisionHandler()
{
    if(collisionToggle){
        static int bColls, nColls = 0;
        octree.clear();

        for (auto object : tabShape)
        {
            octree.insert(object);
        }
        auto colls = octree.getCollisions();
        auto narrowColls = CollisionManager::getNarrowCollision(colls);

        /*cout << "=========================== Broad Collisions ==============================" << endl;
        cout << "Collisions : " <<  colls.size() << endl;
        for (auto& col : colls)
        {
            cout << col.first << " <-> " << col.second << endl;
        }
        cout << "=========================== Narrow Collisions ==============================" << endl;
        cout << "Collisions : " << narrowColls.size()  << endl;
        for (auto& col : narrowColls)
        {
            cout << col.first << " <-> " << col.second << endl;
        } 
        */
        bColls += colls.size();
        nColls += narrowColls.size();
        broadCollisions.setup("Broad Collisions", std::to_string(bColls));
        narrowCollisions.setup("Narrow Collision", std::to_string(nColls));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    collisionHandler();
    checkBoundaries();

    simPause = showForceAdd;
    if (simPause) return;
    // Set the delta time using the last frame time
    updateForces();
    for (auto object : tabShape)
    {
        object->eulerIntegration(delta_t);
    }
    
    delta_t = static_cast<float>(ofGetLastFrameTime()) * simSpeed;
}

/**
 * \brief Draw the interaction area
 */
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
    ofBackground(ofColor::gray);
    cam.begin();
    ofEnableDepthTest();

    for (auto& object : tabShape)
    {
        object->draw();
        if (showDebug && object->linearVelocity.magnitude() > 2)
        {
            ofSetColor(ofColor::greenYellow);
            ofDrawArrow(object->position.v3(), (object->position + object->linearVelocity).v3(), 10);
            ofSetColor(ofColor::white);
        }
    }

    octree.draw(false,"");
    
    //ofDrawGrid(10, VP_SIZE , !showAxis, !showAxis, !showAxis, !showAxis);
    //ofDrawAxis(VP_SIZE);
    ofDisableDepthTest();
    cam.end();
    drawInteractionArea();
    ofSetColor(255);

    controlPanel.draw();
    if (showHelp) helpPanel.draw();
    if (showForceAdd) forcePanel.draw();
    if(collisionToggle) collisionPanel.draw();
    objectPanel.draw();
    if (showDebug   && tabShape.size() > 0)
    {
        debugPanel.draw();
        auto object = tabShape.back();
        updateLines(debugLines1, object->position.to_string());
        updateLines(debugLines2, object->linearVelocity.to_string());
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
    case 'C':
    case 'c':
        cam.getMouseInputEnabled() ? cam.disableMouseInput() : cam.enableMouseInput();
        break;
    case 'F':
    case 'f':
        ofToggleFullscreen();
        break;
    case 'p':
    case 'P':
        showForceAdd = !showForceAdd;
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
    matrixTest.testMatrixMultiplicationByVector();
    matrixTest.testMatrixMultiplicationByScalar();
    matrixTest.testMatrixInverse();
    matrixTest.testMatrixTranspose();
    matrixTest.testMatrixDeterminant();

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
