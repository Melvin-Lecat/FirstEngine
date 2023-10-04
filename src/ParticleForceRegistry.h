#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
class ParticleForceRegistry
{
public:
    struct ParticleForceRegistration
    {
        Particle *particle;
        ParticleForceGenerator *fg;
    };

    typedef std::vector<ParticleForceRegistration> Registre;
    void add(Particle *particle, ParticleForceGenerator *fg);
    void remove(Particle *particle, ParticleForceGenerator *fg);
    void clear();
    void updateForces(float duration);
};
