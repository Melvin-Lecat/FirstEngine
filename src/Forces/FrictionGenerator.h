#pragma once
#include "ForceGenerator.h"
#include "DataStructures/Vector.h"
#include "Objects/RigidBody.h"

class FrictionGenerator: public ForceGenerator
{
public:
    float k1;
    Vector friction;
    FrictionGenerator(float k1);
    void updateForce(RigidBody* object, float duration) override;
};
