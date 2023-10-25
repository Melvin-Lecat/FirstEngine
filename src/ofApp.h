#pragma once

#include "FixedElastic.h"
#include "FixedSpringGenerator.h"
#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "FixedElastic.h"
#include "ParticleForceRegistry.h"
#include "ParticleGravity.h"
#include "ParticleFriction.h"
#include "ParticleSpringGenerator.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void checkUnboundParticules();
    void checkCollision();
    void checkBoundaries();
    void updateForces();
    Vector UpdateCollision(float e, Particle *p1,Particle p2);
    void update();
    void DrawParticle(Particle p);
    void DrawSystem();
    void DrawParticles();
    void draw();
    void SetupBlobGame();

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

    enum SandboxMode
    {
        StaticSpring,
        ParticleSpring,
        StaticElastic,
        ParticleElastic,
        Wire,
        Rod,
        Default
    };
    
    std::list<Particle*> tabParticle;
    float mass;
    float gravity;
    bool simPause = false;

    void clearParticles();

    // Variables to setup the initial parameters of the particle
    Vector particleOrigin = Vector(0, 0, 0);
    Vector particleVelocity = Vector(0, 0, 0);
    ParticleForceRegistry particleForceRegistry;
    Particle currentParticle = Particle(particleVelocity, 1, 9.81f,15.0f);
    bool blobgame = false;
    bool sandbox = false;
    bool debug = false;
    bool enableSpring = false; 
    bool enableGravity = true; 
    bool enableFriction = false; 
    Particle mainParticle;
    
    SandboxMode sbMode = Default;
    Particle firstParticle = Particle(Vector(0,0,0), 1, 9.81f,15.0f);
    Particle secondParticle=Particle(Vector(0,0,0), 1, 9.81f,15.0f);
    bool isFirst = false; 
};

