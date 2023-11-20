#include "RodObject.h"

RodObject::RodObject(Particle* p1, Particle* p2, float K, float length)
{
    this->p1 = p1;
    this->p2 = p2;
    this->K = K;
    this->length = length;
}

void RodObject::CheckCollision()
{
    auto e = 0.9;
    
    auto distance = p1->position.distance(p2->position);

    if(distance < length || distance > length )
    {
        auto direction = (p1->position - p2->position).normalized();
        auto amp = (e + 1) / (p1->getInversedMass() + p2->getInversedMass());
        p1->linearVelocity += direction * amp * (length - distance);
        p2->linearVelocity += direction.opposite() * amp* (length - distance);
        
        /*Vector n = (p1->position - p2->position).normalized();

        auto p1Proj = p1->linearVelocity.projection(n);
        p1->linearVelocity += p1Proj;
        auto p2Proj = p2->linearVelocity.projection(n);
        p2->linearVelocity -= p2Proj;*/
    }
    
}
