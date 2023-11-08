#pragma once
#include "DataStructures/Vector.h"
#include "GameObject.h"

/**
 * @brief A class that represents a rigid body and set the physics for a game object
 * 
 */
class RigidBody: public GameObject
{
public:
    Vector velocity;
    Vector accumForce;

    void eulerIntegration(float delta_t);
    void addForce(Vector force);
    void clearAccum();

    
};
