#include "FixedSpringGenerator.h"

#include "DataStructures/Vector.h"
#include "Objects/Particle.h"

FixedSpringGenerator::FixedSpringGenerator(Vector point, float K, float length)
{
    this->point = point;
    this->K = K;
    this->length = length;
}


void FixedSpringGenerator::updateForce(Particle* particle, float duration)
{
    //cout << "Current length: " << particle->position.distance(point) << endl;
    //cout << "Spring Force: " << glm::abs(length - particle->position.distance(point)) << endl;
    // Direction * K * longueur du ressort
    auto direction = (this->point - particle->position).normalized();
    auto stretch = glm::abs(length - particle->position.distance(point));

    //cout << " ====> Ajout de Ressort" << endl;
    particle->addForce(direction * K * stretch);
}
