#include "GameObject.h"

GameObject::GameObject()
{
    this->gravity = 0;
    this->position = Vector(0, 0, 0);
    this->linearVelocity = Vector(0, 0, 0);
    this->angularVelocity = Vector(0, 0, 0);
    this->linearAcceleration = Vector(0, 0, 0);
}

GameObject::GameObject(float gravity, Vector position, Vector linearVelocity, Vector angularVelocity,
                       Vector linearAcceleration)
{
    this->gravity = gravity;
    this->position = position;
    this->linearVelocity = linearVelocity;
    this->angularVelocity = angularVelocity;
    this->linearAcceleration = linearAcceleration;
}

/**
 * @brief Calculate the distance between this object and another
 * 
 * @param other The other object
 * @return The distance between the two objects
 */
float GameObject::calculateDistance(GameObject* other)
{
    return this->position.distance(other->position);
}

void GameObject::setGravity(float gravity)
{
    this->gravity = gravity;
}

float GameObject::getGravity()
{
    return this->gravity;
}

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
}

void GameObject::setLinearVelocity(Vector linearVelocity)
{
    this->linearVelocity = linearVelocity;
}

void GameObject::setAngularVelocity(Vector angularVelocity)
{
    this->angularVelocity = angularVelocity;
}

void GameObject::setLinearAcceleration(Vector linearAcceleration)
{
    this->linearAcceleration = linearAcceleration;
}

void GameObject::setAngularAcceleration(Vector angularAcceleration)
{
    this->angularAcceleration = angularAcceleration;
}
