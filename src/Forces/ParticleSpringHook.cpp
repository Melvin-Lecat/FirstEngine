#include "ParticleSpringHook.h"

ParticleSpringHook::ParticleSpringHook(Particle *particle, Vector point, float K, float length)
{
    this->particle = particle;   
    this->point = point;   
    this->K = K;   
    this->length = length;   
}

float ParticleSpringHook::distance()
{
    return particle->position.distance(point);   
}

void ParticleSpringHook::updateForce(Particle *particle, float duration)
{
    particle->addForce((this->point-this->particle->position)*K*this->distance());
}
