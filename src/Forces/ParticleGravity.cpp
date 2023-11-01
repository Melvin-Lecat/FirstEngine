#include "ParticleGravity.h"

Vector ParticleGravity::getGravity()
{
    return gravity;
}

ParticleGravity::ParticleGravity(Vector gravity)
{
    this->gravity = gravity;
}

/**
 * @brief Update the particle with a gravity force
 * 
 * @param particle 
 * @param duration 
 */
void ParticleGravity::updateForce(Particle* particle, float duration)
{
    if (particle->getMass() == 0) return;
    particle->addForce(this->gravity * particle->getMass());
}
