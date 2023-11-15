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
    Vector position;

    of3dPrimitive shape;

    GameObject();
    float calculateDistance(GameObject* other);
    void setPosition(Vector newPosition);
};
