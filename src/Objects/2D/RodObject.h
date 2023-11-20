#pragma once
#include "Particle.h"

class RodObject
{
public:
    Particle* p1;
    Particle* p2;
    float length;
    float K;
    float tol = 0.5;

    RodObject(Particle* p1, Particle* p2, float K, float length);
    void CheckCollision();
};
