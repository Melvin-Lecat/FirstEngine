#pragma once
#include "Particle.h"

class CollisionManager2D
{
public:
    static Vector ApplyCollision(float e, Particle* p1, Particle p2);
    static void CheckCollision(std::list<Particle*> tabParticle);
};
