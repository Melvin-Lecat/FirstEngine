#pragma once
#include "Objects/Particle.h"
#include "ParticleForceGenerator.h"
#include "DataStructures/Vector.h"

class ParticleSpringHook : public ParticleForceGenerator
{
public:
    float k;
    float length;
    Particle* particle;
    Vector point;
    ParticleSpringHook(Particle* particle, Vector point, float k, float length);
    float distance();
    void updateForce(Particle* particle, float duration) override;
};
