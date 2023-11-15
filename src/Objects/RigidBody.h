#pragma once
#include "DataStructures/Vector.h"
#include "GameObject.h"
#include "DataStructures/Quaternion.h"

/**
 * @brief A class that represents a rigid body and set the physics for a game object
 * 
 */
class RigidBody : public GameObject
{
public:
    Vector velocity;
    Vector linearVelocity;
    Vector angularVelocity = Vector(10,0,0);
    Vector linearAcceleration;
    Vector angularAcceleration = Vector(0, 0, 0);
    Vector accumForce;
    Quaternion orientation_0 = Quaternion(1, 0, 0, 0);
    float gravity;
    Quaternion orientation = Quaternion(1, 0, 0, 0);


    RigidBody();
    RigidBody(float _gravity, Vector _linearVelocity, Vector _angularVelocity,
              Vector _linearAcceleration);

    void eulerIntegration(float delta_t);
    void addForce(Vector force);
    void clearAccum();

    void setPosition(Vector newPosition);
    float calculateDistance(GameObject* other);
    void setGravity(float gravity);
    float getGravity();
    void setAngularVelocity(Vector angularVelocity);
    void setLinearVelocity(Vector linearVelocity);
    void setAngularAcceleration(Vector angularAcceleration);
    void setLinearAcceleration(Vector linearAcceleration);
    
};
