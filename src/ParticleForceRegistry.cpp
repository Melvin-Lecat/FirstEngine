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
    for (auto item = rg.begin(); item != rg.end();)
    {
        // Check if the particle is out of the screen
        if (item->fg == fg && item->particle == particle)
        {
            // Remove the particle from the list
            item = rg.erase(item);
        }
        else
        {
            // Else, go to the next particle
            ++item;
        }
    }
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