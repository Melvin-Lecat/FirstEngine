#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpringGenerator : public ParticleForceGenerator
{
public:
    float k;
    float length;
    Particle *particle1, *particle2;
    ParticleSpringGenerator(float k, float length, Particle* particle1, Particle* particle2);
    void updateForce(Particle* particle, float duration) override;
};
