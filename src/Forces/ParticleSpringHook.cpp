#include "ParticleSpringHook.h"

ParticleSpringHook::ParticleSpringHook(Particle* particle, Vector point, float k, float length)
{
    this->particle = particle;
    this->point = point;
    this->k = k;
    this->length = length;
}

float ParticleSpringHook::distance()
{
    return particle->position.distance(point);
}

void ParticleSpringHook::updateForce(Particle* particle, float duration)
{
    particle->addForce((this->point - this->particle->position) * k * this->distance());
}
