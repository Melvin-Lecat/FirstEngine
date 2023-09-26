#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void checkUnboundParticules();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void updateParticles(std::list<Particle*> tabParticle, float deltaT);


    Vector pos = Vector(300, 300, 0);
    Vector velocity = Vector(50, 100, 0);
    Particle currentParticle = Particle(velocity, 1, 9.81f);
    std::list<Particle*> tabParticle;
    float mass;
    float gravity;
    bool simPause = false;

    void clearParticles();
};
