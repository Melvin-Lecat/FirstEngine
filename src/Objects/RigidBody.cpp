#include "RigidBody.h"

#include "Particle.h"

RigidBody::RigidBody()
{
    this->gravity = 0;
    this->position = Vector(0, 0, 0);
    this->linearVelocity = Vector(0, 0, 0);
    this->angularVelocity = Vector(0, 10, 0);
    this->linearAcceleration = Vector(0, 0, 0);
    this->angularAcceleration = Vector(0, 0, 1);
    this->orientation_0 = Quaternion(1, 0, 0, 0);
    this->orientation = Quaternion(1, 0, 0, 0);
}

RigidBody::RigidBody(float _gravity, Vector _linearVelocity, Vector _angularVelocity,
                     Vector _linearAcceleration)
{
    this->gravity = _gravity;
    this->linearVelocity = _linearVelocity;
    this->angularVelocity = _angularVelocity;
    this->linearAcceleration = _linearAcceleration;
}


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

    {
        angularVelocity = angularVelocity + angularAcceleration * delta_t;
        orientation = orientation + (Quaternion::toQuaternion(angularVelocity) * orientation) * 0.5 * delta_t;
        orientation = orientation.normalize();
        cout << orientation.magnitude() << endl;
    }

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

/**
 * @brief Calculate the distance between this object and another
 * 
 * @param other The other object
 * @return The distance between the two objects
 */
float RigidBody::calculateDistance(GameObject* other)
{
    return this->position.distance(other->position);
}


void RigidBody::setGravity(float gravity)
{
    this->gravity = gravity;
}

float RigidBody::getGravity()
{
    return this->gravity;
}

void RigidBody::setPosition(Vector newPosition)
{
    this->position = newPosition;
}

void RigidBody::setLinearVelocity(Vector linearVelocity)
{
    this->linearVelocity = linearVelocity;
}

void RigidBody::setAngularVelocity(Vector angularVelocity)
{
    this->angularVelocity = angularVelocity;
}

void RigidBody::setLinearAcceleration(Vector linearAcceleration)
{
    this->linearAcceleration = linearAcceleration;
}

void RigidBody::setAngularAcceleration(Vector angularAcceleration)
{
    this->angularAcceleration = angularAcceleration;
}
