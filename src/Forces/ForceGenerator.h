#pragma once
#include "Objects/RigidBody.h"

class ForceGenerator
{
public:
    virtual void updateForce(RigidBody* object, float duration) = 0;
};
