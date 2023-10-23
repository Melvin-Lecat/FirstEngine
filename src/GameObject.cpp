#include "GameObject.h"

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
}

float GameObject::calculateDistance(GameObject* other)
{
    return this->position.distance(other->position);
}
