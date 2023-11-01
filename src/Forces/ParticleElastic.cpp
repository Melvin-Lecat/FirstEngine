#include "ParticleElastic.h"


void ParticleElastic::updateForce(Particle* particle, float duration)
{
    // Apply the spring force only if the particle is outside the range
    if (particle->position.distance(point) > length)
    {
        FixedSpringGenerator::updateForce(particle, duration);
    }
}
