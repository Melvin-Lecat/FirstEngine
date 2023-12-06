#pragma once

#include "Box.h"
#include "ForceRegistry.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Shape.h"
#include "Cone.h"
#include "FrictionGenerator.h"
#include "GravityGenerator.h"
#include "MatrixTest.h"
#include "Octree.h"
#include "QuaternionTest.h"
#include "VectorTest.h"


# define VP_STEP 50
# define VP_SIZE 250
# define MAX_FORCE 200.0f

// Width is the X axis
# define BOX_WIDTH 40
// Heigth is the Y axis
# define BOX_HEIGTH 20
// Lenght is the Z axis
# define BOX_LENGTH 50

// Radius is the X and Z axis
# define CONE_RADIUS 40
# define CONE_HEIGHT 50

class ofApp : public ofBaseApp
{
public:
    void setupForcePanel();
    void setupDebugPanel();
    void setupObjectPanel();
    void setupControlPanel();
    void setupHelpPanel();
    void setup() override;
    void setBoxType();
    void setConeType();
    void addObject();
    void clearAllObjects();
    void fullscreen();
    void togglePause();
    void launchObject();
    void addMultiLineText(ofxPanel& panel, std::vector<ofxLabel*>& lines, const std::string& text);
    void checkBoundaries();
    void updateForces();
    void addForceObject(Shape &obj, Vector forceIntensity, Vector pointApplication);
    void update() override;
    void drawInteractionArea();
    void draw() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;

    float delta_t = 0.01f;
    float gravity;
    
    float simSpeed= 2.0f;
    bool simPause = false;

    

    ForceRegistry forceRegistry;
    std::list<Shape*> tabShape;

    //Cone object = Cone(40, 80);
    //Box object = Box(20, 20, 20);
    ofEasyCam cam;


    // GUI Objects
    ofxPanel helpPanel, controlPanel, debugPanel, forcePanel, objectPanel;
    std::vector <ofxLabel*> helpLines;
    std::vector <ofxLabel*> lines;
    // todo toggle ?

    // Control panel elements
    ofxToggle showHelp, showDebug, showAxis, showForceAdd, gravityToggle, frictionToggle; 

    ofxButton fullscreenButton;
    ofxButton gamePaused;
    ofxButton clearAll;

    // Help panel elements
    std::string manualText =
        
        "While adding an object, \n the initial force is applied on [0,0,0]\n"
        "Enabling the debug panel, will show informations on the last added obect to the viewport. \n"
        "The same goes for the force panel \n"
        "Keyboard shortcut are enabled to control the application \n"
        "Pressing 'spacebar' will enable orthographic camera \n"
        "Pressing 'f' will enable fullscreen \n"
        "Pressing 'c' will disable mouse interaction with the simulation \n"
        "Pressing 'p' will pause the simulation \n"
        "Pressing 'esc' will exit the application \n"; 

    // Debug panel elements
    ofxLabel position,velocity;
     std::vector <ofxLabel*>  debugLines1, debugLines2;
    
    // Force panel elements
    ofxLabel positionForceLabel;
    ofxFloatSlider xpInput, ypInput, zpInput;
    ofxLabel intensityForceLabel;
    ofxFloatSlider xvInput, yvInput, zvInput;
    ofxButton launch;
    
    // Object panel elements
    ofxLabel cdmObjectLabel;
    ofxFloatSlider xpInputObject, ypInputObject, zpInputObject;
    ofxLabel objectTypeLabel;
    ofxButton boxButton,coneButton, addButton;
    ofxLabel initialForceLabel;
    ofxFloatSlider xfInput, yfInput, zfInput;
   
    bool GameState = false;


    enum ObjectType
    {
        BOX,
        CONE
    };

    ObjectType objectType = BOX;

    Octree octree = Octree(Vector(0,0,0), VP_SIZE,VP_SIZE,VP_SIZE,0);

    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
    void quaternionTests();
};
