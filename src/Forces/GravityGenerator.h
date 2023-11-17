#pragma once
#include "ForceGenerator.h"

class GravityGenerator: public ForceGenerator
{
public:
public:
    Vector gravity;
    Vector getGravity();
    GravityGenerator(Vector gravity);
    void updateForce(RigidBody* object, float duration) override;
};
