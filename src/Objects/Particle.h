#pragma once
#include "DataStructures/Vector.h"
#include "RigidBody.h"

class Particle : public RigidBody
{
protected:
    float inversedMass;

public:
    
    float time;
    float radius;

    // Constructors
    Particle();
    Particle(Vector velocity, float mass);
    Particle(Vector velocity, float mass, float radius);
    Particle(Vector velocity, float mass, float radius, float gravity);
    Particle(Vector velocity, float mass, int r, int g, int b, float radius);

    // Methods
    float getMass();
    float getInversedMass();
    void setMass(float m);
    Particle* duplicate();
    //TODO: setup function
    
};
