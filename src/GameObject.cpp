#include "GameObject.h"

void GameObject::setPosition(Vector newPosition)
{
    this->position = newPosition;
}

float GameObject::calculateDistance(GameObject* other)
{
    return glm::sqrt(glm::pow2(this->position.x - other->position.x) + glm::pow2(this->position.y - other->position.y) + glm::pow2(this->position.z - other->position.z));
}
