#include "ParticleSpringGenerator.h"

#include "FixedSpringGenerator.h"

ParticleSpringGenerator::ParticleSpringGenerator(float K, float length, Particle* particle1, Particle* particle2)
{
    this->K = K;
    this->length = length;
    this->particle1 = particle1;
    this->particle2 = particle2;
}

void ParticleSpringGenerator::updateForce(Particle *particle, float duration)
{
    FixedSpringGenerator fsg1 (particle2->position, K, length);
    FixedSpringGenerator fsg2 (particle1->position, K, length);
    fsg1.updateForce(particle1, duration);
    fsg2.updateForce(particle2, duration);
}

