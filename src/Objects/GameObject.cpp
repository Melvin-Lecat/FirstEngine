#include "GameObject.h"

GameObject::GameObject()
{
    this->position = Vector(0, 0, 0);
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

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
}