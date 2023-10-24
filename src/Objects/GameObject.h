#pragma once
#include "DataStructures/Vector.h"

class GameObject
{
        
    public:
    int color[3] = {255, 255, 255};
    Vector position;

    void setPosition(Vector newPosition);
    float calculateDistance(GameObject *other);


    
};
