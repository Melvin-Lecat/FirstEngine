#include "ParticleGravity.h"

Vector ParticleGravity::getGravity()
{
    return gravity;
}

void ParticleGravity::setGravity(Vector gravity)
{
    this->gravity.x = gravity.x;
    this->gravity.y = gravity.y;
    this->gravity.z = gravity.z;
}

void ParticleGravity::updateForce(Particle *particle, float duration)
{
    if (particle->getMass()!=0)
    {
        particle->addForce(this->gravity*particle->getMass());
    }
}
