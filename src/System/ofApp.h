#pragma once

#include "ofMain.h"
#include "DataStructures/Vector.h"
#include "Forces/ForceRegistry.h"
#include "Objects/Box.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void TogglePause();
    void AddMultiLineText(ofxPanel& _panel, std::vector<ofxLabel*>& _lines, std::string _text);
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
    bool showAxis = true;

    Vector firstP, secP;
    bool drawLine = false; 

    // GUI Objects
    ofxPanel helpPanel, controlPanel, debugPanel;
    std::vector <ofxLabel*> lines;

    // todo toggle ?
    ofxButton gamePaused ;

    
    
    std::string multilineText = "\n"
        "Press 'p' to pause simulation\n"
        "Press 'i' to clear all bullets\n"
        "Press 'o' to fire the current bullet (default : standard)\n"
        "Press the right arrow to update frame by frame while paused\n"
        "Click in the window to change the initial velocity\n"
        "Press 'a' to fire a standard bullet\n"
        "Press 'z' to fire a laser like bullet\n"
        "Press 'e' to fire a heavy bullet\n"
        "Press 'r' to fire a very heavy bullet\n"
        "Press 't' to fire a custom bullet\n";
    bool GameState = false;


    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
    void quaternionTests();
};
