#pragma once
#include "FixedSpringGenerator.h"

class FixedElastic : public ParticleForceGenerator
{
public:
    float K;
    float length;
    Vector point;
    //ParticleSpringHook(Particle *particle1, Particle *particle2, float K, float length);
    FixedElastic(Vector point, float K, float length);
    void updateForce(Particle *particle, float duration);
};
