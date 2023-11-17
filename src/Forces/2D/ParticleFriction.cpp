#include "ParticleFriction.h"

ParticleFriction::ParticleFriction(float k1)
{
    this->k1 = k1;
}

/**
 * @brief Update the particle with a friction force
 * 
 * @param particle 
 * @param duration 
 */
void ParticleFriction::updateForce(Particle* particle, float duration)
{
    particle->addForce(particle->linearVelocity * (-k1));
}
