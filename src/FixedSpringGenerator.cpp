#include "FixedSpringGenerator.h"

FixedSpringGenerator::FixedSpringGenerator(Vector point, float K, float length)
{
    this->point = point;   
    this->K = K;   
    this->length = length;   
}



void FixedSpringGenerator::updateForce(Particle *particle, float duration)
{
   
    // Direction * K * longueur du ressort
    auto direction = (this->point-particle->position).normalized();
    auto stretch = glm::abs(length - particle->position.distance(point));
    
    //cout << " ====> Ajout de Ressort" << endl;
    particle->addForce( direction*K*stretch);
}


