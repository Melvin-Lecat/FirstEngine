#include "ParticleForceRegistry.h"


void ParticleForceRegistry::add(Particle *particle, ParticleForceGenerator *fg)
{
    struct ParticleForceRegistration var;
    var.particle = particle;
    var.fg = fg;
    rg.push_back(var);
}

void ParticleForceRegistry::remove(Particle *particle, ParticleForceGenerator *fg)
{
    struct ParticleForceRegistration var;
    var.particle = particle;
    var.fg = fg;
    
    //rg.erase(var);
}

void ParticleForceRegistry::clear()
{
    
}

void ParticleForceRegistry::updateForces(float duration)
{
    
}