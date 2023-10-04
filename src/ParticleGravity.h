#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
public:
    Vector gravity;
    Vector getGravity();
    void setGravity(Vector gravity);
    virtual void updateForce(Particle *particle, float duration);
};
