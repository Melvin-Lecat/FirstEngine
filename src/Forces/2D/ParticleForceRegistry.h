#pragma once
#include <vector>

#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
public:
    struct ParticleForceRegistration
    {
        Particle* particle;
        ParticleForceGenerator* fg;
    };

    using Registre = std::vector<ParticleForceRegistration>;
    Registre rg;
    void add(Particle* particle, ParticleForceGenerator* fg);
    void remove(Particle* particle, ParticleForceGenerator* forceGenerator);
    void clear();
    void updateForces(float duration);
};
