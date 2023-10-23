#include "FixedSpringGenerator.h"

FixedSpringGenerator::FixedSpringGenerator(Vector point, float K, float length)
{
    this->point = point;   
    this->K = K;   
    this->length = length;   
}



void FixedSpringGenerator::updateForce(Particle *particle, float duration)
{
   
    cout << "Current length: " << particle->position.distance(point) << endl;
    cout << "Spring Force: " << glm::abs(length - particle->position.distance(point)) << endl;
    // Direction * K * longueur du ressort
    particle->addForce((this->point-particle->position).normalized()*K*glm::abs(length - particle->position.distance(point)));
}
