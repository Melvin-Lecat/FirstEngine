#include "FixedElastic.h"

void FixedElastic::updateForce(Particle* particle, float duration)
{
    cout << "Current length: " << particle->position.distance(point) << endl;
    cout << "Spring Force: " << glm::abs(length - particle->position.distance(point)) << endl;
    if (particle->position.distance(point) > length)
    {
        // Direction * K * longueur du ressort
            particle->addForce(
                (this->point - particle->position).normalized() * K * glm::abs(length - particle->position.distance(point)));
    }
}
