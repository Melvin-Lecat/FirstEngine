#include "ParticleFriction.h"

ParticleFriction::ParticleFriction(float k1, float k2)
{
    this->k1 = k1;
    this->k2 = k2;
}


void ParticleFriction::updateForce(Particle* particle, float duration)
{
    particle->addForce(
    particle->velocity.normalized().opposite() * (this->k1 * particle->velocity.magnitude() + this->k2 *glm::pow2(particle->
        velocity.magnitude())));
}
