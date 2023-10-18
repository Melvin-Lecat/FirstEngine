#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void checkUnboundParticules();
    void checkCollision();
    void checkBoundaries();
    void updateForces();
    void update();
    void DrawParticle(Particle p);
    void DrawSystem();
    void DrawParticles();
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


    
    
    std::list<Particle*> tabParticle;
    float mass;
    float gravity;
    bool simPause = false;

    void clearParticles();

    // Variables to setup the initial parameters of the particle
    Vector particleOrigin = Vector(0, 0, 0);
    Vector particleVelocity = Vector(0, 0, 0);
    ParticleForceRegistry particleForceRegistry;
    Particle currentParticle = Particle(particleVelocity, 1, 9.81f);
    bool blobgame = false;
};
