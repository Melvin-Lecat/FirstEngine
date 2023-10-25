#pragma once
#include "FixedSpringGenerator.h"

class FixedElastic: public FixedSpringGenerator
{
public:
    void updateForce(Particle* particle, float duration) override;
    
};
