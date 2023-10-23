#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector.h"

class ParticleFriction:public ParticleForceGenerator
{
public:
    float k1;
    float k2;
    Vector friction;
    ParticleFriction(float k1,float k2);
    void updateForce(Particle *particle, float duration);
};