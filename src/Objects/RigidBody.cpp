#include "RigidBody.h"

#include "Particle.h"

RigidBody::RigidBody()
{
    this->gravity = 0;
    this->position = Vector(0, 0, 0);
    this->linearVelocity = Vector(0, 0, 0);
    this->angularVelocity = Vector(0, 0, 0);
    this->linearAcceleration = Vector(0, 0, 0);
    this->angularAcceleration = Vector(0, 0, 0);
    this->orientation_0 = Quaternion(1, 0, 0, 0);
    this->orientation = Quaternion(1, 0, 0, 0);
    // todo verification récupération de tenseur venant bien de box
    
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
 * @brief Calculate the new position of the object using the Euler integration method
 * 
 * @param delta_t 
 */
void RigidBody::eulerIntegration(float delta_t)
{
    // Update the velocity of the object...
    linearVelocity += accumForce * delta_t;

    // ... and its position
    position += linearVelocity * delta_t;

    {
        updateInversedJ();
        calculateAngularAcceleration();
        
        angularVelocity = angularVelocity + angularAcceleration * delta_t;
        orientation = orientation + (Quaternion::toQuaternion(angularVelocity) * orientation) * 0.5 * delta_t;
        orientation = orientation.normalize();
        cout << orientation.magnitude() << endl;
    }

    clearAccum();
    angularAcceleration = Vector(0, 0, 0);
}

/**
 * @brief Add a force to the object
 * 
 * @param force 
 */

void RigidBody::addForce(Vector force)
{
    this->accumForce += force;
}

void RigidBody::addForce(Vector force, Vector pointApplication)
{
    this->accumForce += force;
    Vector l(0,0,0);
    l.x = abs(pointApplication.x - position.x);
    l.y = abs(pointApplication.y - position.y);
    l.z = abs(pointApplication.z - position.z);
    this->torque = torque + (l.vectorialProduct(force));
}

/**
 * @brief Clear the forces associated to the object
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

void RigidBody::calculateAngularAcceleration()
{
    setAngularAcceleration(Vector(torque.x * inversedTenseurJ.l1.x + torque.y * inversedTenseurJ.l2.x + torque.z * inversedTenseurJ.l3.x,
        torque.x * inversedTenseurJ.l1.y + torque.y * inversedTenseurJ.l2.y + torque.z * inversedTenseurJ.l3.y,
        torque.x * inversedTenseurJ.l1.z + torque.y * inversedTenseurJ.l2.z + torque.z * inversedTenseurJ.l3.z));
}

void RigidBody::updateInversedJ()
{
    inversedTenseurJ = (orientation.quatToMat() * inversedTenseurJ) * orientation.quatToMat().inverse();
}

void RigidBody::moveCenterMass(Vector translation)
{
    tenseurJ = tenseurJ + (Matrix(Vector(glm::pow2(translation.y) + glm::pow2(translation.z) , -translation.x * translation.y , -translation.x * translation.z), Vector(-translation.x * translation.y , glm::pow2(translation.x) + glm::pow2(translation.z) , -translation.y * translation.z), Vector(-translation.x * translation.z , -translation.y * translation.z , glm::pow2(translation.x) + glm::pow2(translation.y))) * getMass() );
}