#pragma once
#include "ParticleForceGenerator.h"

class FixedSpringGenerator : public ParticleForceGenerator
{
public:
    float k;
    float length;
    Vector point;
    FixedSpringGenerator(Vector point, float k, float length);
    void updateForce(Particle* particle, float duration) override;
};
