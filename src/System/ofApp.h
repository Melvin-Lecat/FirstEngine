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
    Particle currentParticle = Particle(particleVelocity, 1, 9.81f, 15.0f);
    bool blobgame = false;
    Particle mainParticle;

    ofCamera camera;
    Box boxObject = Box(100, 200, 300);
    ofEasyCam cam;
    ofBoxPrimitive box;

    // Tests methods
    void unitTests();
    void vectorTests();
    void matrixTests();
};
