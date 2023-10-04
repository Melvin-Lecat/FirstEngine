#include "ParticleGravity.h"

Vector ParticleGravity::getGravity()
{
    return this->gravity;
}

void ParticleGravity::setGravity(Vector gravity)
{
    this->gravity = gravity;
}

void ParticleGravity::updateForce(Particle *particle, float duration)
{
    if (particle->getMass()==0) return;
    particle->addForce(this->gravity*particle->getMass());
}
