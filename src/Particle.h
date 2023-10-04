#pragma once
#include "Vector.h"

class Particle
{
protected:
    float inversedMass;

public:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector accumForce;
    float time;
    int color[3] = {255, 255, 255};

    // Constructors
    Particle();
    Particle(Vector velocity, float mass);
    Particle(Vector velocity, float mass, float gravity);
    Particle(Vector velocity, float mass, float gravity, bool massInfluence);
    Particle(Vector velocity, float mass, float gravity, int r, int g, int b);

    // Methods
    float getMass();
    void setMass(float m);
    void setPosition(Vector newPosition);
    void eulerIntegration(float delta_t);
    Particle* duplicate();
    void addForce(Vector force);
    void clearAccum();
};
