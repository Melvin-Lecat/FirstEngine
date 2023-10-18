#include "SpringGenerator.h"

SpringGenerator::SpringGenerator(Vector point, float K, float length)
{
    this->point = point;   
    this->K = K;   
    this->length = length;   
}



void SpringGenerator::updateForce(Particle *particle, float duration)
{
    particle->addForce((this->point-particle->position)*K*glm::abs(length - particle->position.distance(point)));
}
