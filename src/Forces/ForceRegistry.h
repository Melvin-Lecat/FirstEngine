#pragma once
#include "ForceGenerator.h"
#include "Objects/RigidBody.h"

class ForceRegistry
{
public:
    struct ForceRegistration
    {
        RigidBody* object;
        ForceGenerator* fg;
    };

    using Registre = std::vector<ForceRegistration>;
    Registre rg;
    void add(RigidBody* object, ForceGenerator* fg);
    void remove(RigidBody* object, ForceGenerator* forceGenerator);
    void clear();
    void updateForces(float duration);
};
