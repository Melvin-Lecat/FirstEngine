#pragma once

#include "Box.h"
#include "ForceRegistry.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Shape.h"

class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void setBoxType();
    void setConeType();
    void AddObject();
    void Fullscreen();
    void TogglePause();
    void LaunchObject();
    void AddMultiLineText(ofxPanel& _panel, std::vector<ofxLabel*>& _lines, const std::string& _text);
    void checkBoundaries();
    void updateForces();
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
    std::list<Shape> tabShape;

    Box object = Box(20, 20, 20);
    ofEasyCam cam;

    Vector firstP, secP;
    bool drawLine = false; 

    // GUI Objects
    ofxPanel helpPanel, controlPanel, debugPanel, forcePanel, objectPanel;
    std::vector <ofxLabel*> helpLines;
    std::vector <ofxLabel*> lines;
    // todo toggle ?

    // Control panel elements
    ofxToggle showHelp, showDebug, showAxis, showForceAdd, showObjectAdd; 

    ofxButton fullscreenButton;
    ofxButton gamePaused;
    ofxButton clearAll;

    // Help panel elements

    std::string manualText = 
           "Press 'p' to pause simulation\n"
           "Press 'i' to clear all bullets\n"
           "Press 'o' to fire the current bullet (default : standard)\n"
           "Press the right arrow to update frame by frame while paused\n"
           "Click in the window to change the initial velocity\n"
           "Press 'a' to fire a standard bullet\n"
           "Press 'z' to fire a laser like bullet\n"
           "Press 'e' to fire a heavy bullet\n"
           "Press 'r' to fire a very heavy bullet\n"
           "Press 't' to fire a custom bullet";
    
    // Debug panel elements
    ofxLabel position,velocity;
     std::vector <ofxLabel*>  debugLines1, debugLines2;
    // Force panel elements
    ofxLabel positionForceLabel;
    ofxFloatSlider xpInput, ypInput, zpInput;
    ofxLabel velocityForceLabel;
    ofxFloatSlider xvInput, yvInput, zvInput;
    ofxButton launch;
    // Object panel elements
    ofxLabel cdmObjectLabel;
    ofxFloatSlider xpInputObject, ypInputObject, zpInputObject;
    ofxLabel objectTypeLabel;
    ofxButton boxButton,coneButton, addButton; 
   
    bool GameState = false;


    enum ObjectType
    {
        BOX,
        CONE
    };

    ObjectType objectType = BOX;
    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
    void quaternionTests();
};
