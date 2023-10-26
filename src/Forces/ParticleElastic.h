#pragma once
#include "FixedSpringGenerator.h"

class ParticleElastic: public FixedSpringGenerator
{
public:
    void updateForce(Particle* particle, float duration) override;
    
};
