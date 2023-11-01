#include "GameObject.h"

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
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
