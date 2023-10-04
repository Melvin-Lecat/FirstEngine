#include "ParticleGravity.h"

Vector ParticleGravity::getGravity()
{
}

void ParticleGravity::setGravity(Vector gravity)
{
}

void ParticleGravity::updateForce(Particle *particle, float duration)
{
    if (particle->getMass()!=0)
    {
        particle->addForce(this->gravity*particle->getMass());
    }
}
