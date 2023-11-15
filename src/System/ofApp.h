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
    void setup();
    void checkUnboundParticules();
    void checkBoundaries();
    void updateForces();
    void update() ;
    void DrawParticle(Particle p);
    void DrawSystem();
    void DrawParticles();
    void drawInteractionArea();
    void draw() ;
    void SetupBlobGame();

    void keyPressed(int key) ;
    void keyReleased(int key) ;
    void mouseMoved(int x, int y) ;
    void mouseDragged(int x, int y, int button) ;
    void mousePressed(int x, int y, int button) ;
    void mouseReleased(int x, int y, int button) ;
    void mouseEntered(int x, int y) ;
    void mouseExited(int x, int y) ;
    void windowResized(int w, int h) ;
    void dragEvent(ofDragInfo dragInfo) ;
    void gotMessage(ofMessage msg) ;
    void updateParticles(std::list<Particle*> tabParticle, float deltaT);


    std::list<Particle*> tabParticle;
    float mass;
    float gravity;
    bool simPause = false;

    void clearParticles();
    void unitTests();
    void vectorTests();

    // Variables to setup the initial parameters of the particle
    Vector particleOrigin = Vector(0, 0, 0);
    Vector particleVelocity = Vector(0, 0, 0);
    ParticleForceRegistry particleForceRegistry;
    Particle currentParticle = Particle(particleVelocity, 1, 9.81f, 15.0f);
    bool blobgame = false;
    Particle mainParticle;

    ofCamera camera;
    Box boxObject = Box(1, 2, 3);
    ofEasyCam cam;
    ofBoxPrimitive box;
};
