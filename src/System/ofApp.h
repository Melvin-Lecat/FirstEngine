#pragma once

#include "ofMain.h"
#include "DataStructures/Vector.h"
#include "Forces/ForceRegistry.h"
#include "Objects/Box.h"

class ofApp : public ofBaseApp
{
public:
    void setup() override;
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

    bool GameState = false;


    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
};
