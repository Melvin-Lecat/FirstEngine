#include "ParticleForceRegistry.h"


void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
    struct ParticleForceRegistration var;
    var.particle = particle;
    var.fg = fg;
    rg.push_back(var);
}

/**
 * Remove a particle from the registry
 * @param particle
 * @param forceGenerator
 */
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* forceGenerator)
{
    for (auto item = rg.begin(); item != rg.end();)
    {
        // Check if the particle is out of the screen
        if (item->fg == forceGenerator && item->particle == particle)
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

/**
 * @brief Clear the registry
 */
void ParticleForceRegistry::clear()
{
    rg.clear();
}

/**
 * @brief Update the forces of all the particles
 * 
 * @param duration 
 */
void ParticleForceRegistry::updateForces(float duration)
{
    for (auto& var : rg)
    {
        var.fg->updateForce(var.particle, duration);
    }
    clear();
}
