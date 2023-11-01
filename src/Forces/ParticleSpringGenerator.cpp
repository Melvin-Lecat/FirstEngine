#include "ParticleSpringGenerator.h"

#include "FixedSpringGenerator.h"

ParticleSpringGenerator::ParticleSpringGenerator(float k, float length, Particle* particle1, Particle* particle2)
{
    this->k = k;
    this->length = length;
    this->particle1 = particle1;
    this->particle2 = particle2;
}

/**
 * @brief Update both particles with a spring force between them
 * 
 * @param particle 
 * @param duration 
 */
void ParticleSpringGenerator::updateForce(Particle* particle, float duration)
{
    FixedSpringGenerator fsg1(particle2->position, k, length);
    FixedSpringGenerator fsg2(particle1->position, k, length);
    fsg1.updateForce(particle1, duration);
    fsg2.updateForce(particle2, duration);
}
