#include "FixedSpringGenerator.h"

#include "DataStructures/Vector.h"
#include "Objects/Particle.h"

FixedSpringGenerator::FixedSpringGenerator(Vector point, float k, float length)
{
    this->point = point;
    this->k = k;
    this->length = length;
}

/**
 * @brief Update the particle with a spring force
 * 
 * @param particle 
 * @param duration 
 */
void FixedSpringGenerator::updateForce(Particle* particle, float duration)
{
    // Calculate the direction of the spring
    Vector direction = (this->point - particle->position).normalized();
    // Calculate the stretch of the spring
    float stretch = glm::abs(length - particle->position.distance(point));

    // Apply the force
    particle->addForce(direction * k * stretch);
}
