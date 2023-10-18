#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector.h"

class SpringGenerator:public ParticleForceGenerator
{
public:
    float K;
    float length;
    Vector point;
    //ParticleSpringHook(Particle *particle1, Particle *particle2, float K, float length);
    SpringGenerator(Vector point, float K, float length);
    void updateForce(Particle *particle, float duration);
};
