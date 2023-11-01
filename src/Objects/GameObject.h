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

    void setPosition(Vector newPosition);
    float calculateDistance(GameObject* other);
    void setGravity(float gravity);
    float getGravity();
};
