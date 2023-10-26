#pragma once
#include "Objects/Particle.h"
#include "ParticleForceGenerator.h"
#include "DataStructures/Vector.h"

class ParticleSpringHook:public ParticleForceGenerator
{
public:
    float K;
    float length;
    Particle *particle;
    Vector point;
    //ParticleSpringHook(Particle *particle1, Particle *particle2, float K, float length);
    ParticleSpringHook(Particle *particle, Vector point, float K, float length);
    float distance();
    void updateForce(Particle *particle, float duration);
};
