#pragma once
#include "Vector.h"
#include "GameObject.h"

class Particle:GameObject
{
protected:
    float inversedMass;

public:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector accumForce;
    float time;
    float radius;

    // Constructors
    Particle();
    Particle(Vector velocity, float mass);
    Particle(Vector velocity, float mass, float gravity);
    Particle(Vector velocity, float mass, float gravity, bool massInfluence);
    Particle(Vector velocity, float mass, int r, int g, int b);
    Particle(Vector velocity, float mass, int r, int g, int b, float radius);

    // Methods
    float getMass();
    void setMass(float m);
    void setPosition(Vector newPosition);
    void eulerIntegration(float delta_t);
    Particle* duplicate();
    void addForce(Vector force);
    void clearAccum();
};
