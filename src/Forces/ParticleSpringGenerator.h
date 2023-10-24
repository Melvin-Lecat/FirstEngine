#pragma once
#include "Objects/Particle.h"
#include "ParticleForceGenerator.h"

class ParticleSpringGenerator : public ParticleForceGenerator
{
public:
    float K;
    float length;
    Particle *particle1, *particle2;
    ParticleSpringGenerator(float K, float length, Particle *particle1, Particle *particle2);
    void updateForce(Particle *particle, float duration);
};
