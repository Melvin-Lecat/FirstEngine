#include "RigidBody.h"

#include "Particle.h"

/**
 * @brief Calculate the new position of the particle using the Euler integration method
 * 
 * @param delta_t 
 */
void RigidBody::eulerIntegration(float delta_t)
{
    // TODO: Update the implementation
    // Update the velocity of the particle...
    velocity += accumForce * delta_t * pow(0.2, delta_t);

    // ... and its position
    position += velocity * delta_t;
    clearAccum();
}

/**
 * @brief Add a force to the particle
 * 
 * @param force 
 */
void RigidBody::addForce(Vector force)
{
    this->accumForce += force;
}

/**
 * @brief Clear the forces associated to the particle
 * 
 */
void RigidBody::clearAccum()
{
    this->accumForce = Vector(0, 0, 0);
}
