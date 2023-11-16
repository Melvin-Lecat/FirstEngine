#pragma once

#include "ofMain.h"
#include "DataStructures/Quaternion.h"
#include "DataStructures/Vector.h"
#include "Objects/Particle.h"
#include "Forces/ParticleForceRegistry.h"
#include "Objects/Box.h"

class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void checkUnboundParticles();
    void checkUnboundParticules();
    void checkBoundaries();
    void updateForces();
    void update() override;
    void DrawParticle(Particle p);
    void DrawSystem();
    void DrawParticles();
    void drawInteractionArea();
    void draw() override;
    void SetupBlobGame();

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


    float gravity;
    bool simPause = false;


    

    ParticleForceRegistry particleForceRegistry;
    std::list<Box> tabBox;

    Box boxObject = Box(10, 20, 30);
    ofEasyCam cam;
    bool showAxis = true;

    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
};
