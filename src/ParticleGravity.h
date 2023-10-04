#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector.h"

class ParticleGravity:public ParticleForceGenerator
{
public:
    Vector gravity;
    Vector getGravity();
    void setGravity(Vector gravity);
    void updateForce(Particle *particle, float duration);
};
