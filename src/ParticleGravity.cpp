#include "ParticleGravity.h"

virtual void updateForce(Particle *particle, float duration)
{
    if (particle->getMass()!=0)
    {
        particle->addForce(ParticleGravity*particle->getMass());
    }
}