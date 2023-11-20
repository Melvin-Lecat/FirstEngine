
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
    auto e = 0.9;
    float distance = p1->position.distance(p2->position);
    if(distance > length)
    {
        auto direction = (p1->position - p2->position).normalized();
        auto amp = (e + 1) / (p1->getInversedMass() + p2->getInversedMass());
        p1->linearVelocity += direction.opposite() * K *amp ;
        p2->linearVelocity += direction * K * amp;
    }
}

