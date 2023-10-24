#pragma once
#include "Particle.h"

class WireObject
{
public:
    Particle* p1;
    Particle* p2;
    float length;
    float K;

    WireObject(Particle* p1, Particle* p2, float K, float length);
    void CheckCollision();
    
    
};

