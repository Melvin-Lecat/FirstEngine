#pragma once
#include "Particle.h"

class ParticleForceGenerator
{
public:
    // Virtual method to be implemented by the child classes
    virtual void updateForce(Particle* particle, float duration) = 0;
};
