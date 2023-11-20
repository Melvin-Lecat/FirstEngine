#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
public:
    Vector gravity;
    Vector getGravity();
    ParticleGravity(Vector gravity);
    void updateForce(Particle* particle, float duration) override;
};
