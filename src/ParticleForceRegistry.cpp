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

    //remove var from rg
    //rg.erase(std::remove(rg.begin(), rg.end(), var), rg.end()); //todo: a tester
}

void ParticleForceRegistry::clear()
{
    rg.clear();
}

void ParticleForceRegistry::updateForces(float duration)
{
    for (auto &var : rg)
    {
        var.fg->updateForce(var.particle, duration);
    }
    clear();
}