#pragma once
#include "DataStructures/Vector.h"

/**
 * @brief An abstract class that represents a game object and set global properties
 * 
 */
class GameObject
{
public:
    int color[3] = {255, 255, 255};
    float gravity;
    Vector position;
    Vector linearVelocity;
    Vector angularVelocity;
    Vector linearAcceleration;
    Vector angularAcceleration = Vector(0, 0, 0);
    of3dPrimitive shape;

    GameObject();
    GameObject(float gravity, Vector position, Vector linearVelocity, Vector angularVelocity,
               Vector linearAcceleration);

    void setPosition(Vector newPosition);
    float calculateDistance(GameObject* other);
    void setGravity(float gravity);
    float getGravity();
    void setAngularVelocity(Vector angularVelocity);
    void setLinearVelocity(Vector linearVelocity);
    void setAngularAcceleration(Vector angularAcceleration);
    void setLinearAcceleration(Vector linearAcceleration);
};
