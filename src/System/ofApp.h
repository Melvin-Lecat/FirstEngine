#pragma once

#include "Box.h"
#include "Cone.h"
#include "ForceRegistry.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Shape.h"

class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void TogglePause();
    void AddMultiLineText(ofxPanel& panel, std::vector<ofxLabel*>& lines, const std::string& text);
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
    std::list<Shape> tabShape;

    Cone object = Cone(40, 80);
    //Box object = Box(20, 20, 20);
    ofEasyCam cam;
    bool showAxis = true;

    Vector firstP, secP;
    bool drawLine = false; 

    // GUI Objects
    ofxPanel helpPanel, controlPanel, debugPanel;
    std::vector <ofxLabel*> helpLines,debugLines1, debugLines2;
    std::vector <ofxLabel*> lines;
    // todo toggle ?
    ofxButton gamePaused ;
    ofxLabel position,velocity;
    
    std::string multilineText = 
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
    bool GameState = false;


    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
    void quaternionTests();
};
