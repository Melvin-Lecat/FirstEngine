#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector.h"

class FixedSpringGenerator:public ParticleForceGenerator
{
public:
    float K;
    float length;
    Vector point;
    //ParticleSpringHook(Particle *particle1, Particle *particle2, float K, float length);
    FixedSpringGenerator(Vector point, float K, float length);
    void updateForce(Particle *particle, float duration);
};
