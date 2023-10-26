#pragma once
#include "ParticleForceGenerator.h"
#include "DataStructures/Vector.h"
#include "Objects/Particle.h"

class FixedSpringGenerator : public ParticleForceGenerator
{
public:
    float K;
    float length;
    Vector point;
    //ParticleSpringHook(Particle *particle1, Particle *particle2, float K, float length);
    FixedSpringGenerator(Vector point, float K, float length);
    void updateForce(Particle* particle, float duration);
};
