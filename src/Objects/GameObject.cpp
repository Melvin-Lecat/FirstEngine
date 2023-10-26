#include "GameObject.h"

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
}

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
