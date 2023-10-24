
#include "WireObject.h"

WireObject::WireObject(Particle *p1, Particle* p2, float K, float length)
{
    this->p1 = p1;
    this->p2 = p2;
    this->K = K;
    this->length = length;
}

void WireObject::CheckCollision()
{
    float distance = p1->position.distance(p2->position);
    if(distance > length)
    {
        p1->velocity = Vector(0, 0, 0);
        p2->velocity = Vector(0, 0, 0);
    }
}

