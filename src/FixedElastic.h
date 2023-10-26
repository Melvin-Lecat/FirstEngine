#pragma once
#include "FixedSpringGenerator.h"

class FixedElastic : public ParticleForceGenerator
{
public:
    float K;
    float length;
    Vector point;
    FixedElastic(Vector point, float K, float length);
    void updateForce(Particle *particle, float duration);
};

