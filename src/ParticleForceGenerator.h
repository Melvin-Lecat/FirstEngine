#pragma once
#include "Particle.h"

class ParticuleForceGenerator
{
public:
    virtual void updateForce(Particle *particle, float duration) = 0;
};
