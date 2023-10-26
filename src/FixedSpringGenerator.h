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
    FixedSpringGenerator(Vector point, float K, float length);
    void updateForce(Particle *particle, float duration);
};

