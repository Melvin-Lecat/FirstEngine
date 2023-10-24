#pragma once
#include "Objects/Particle.h"
#include "ParticleForceGenerator.h"
#include "DataStructures/Vector.h"

class ParticleGravity:public ParticleForceGenerator
{
public:
    Vector gravity;
    Vector getGravity();
    ParticleGravity(Vector gravity);
    void updateForce(Particle *particle, float duration);
};
