#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
private:

public:
    float getWidth()
    {
        return width;
    }
        
    float getHeight()
    {
        return height;
    }
    float getDepth()
    {
        return depth;
    }

private:
    
    float width;
    float height;
    float depth;

public:
    Box();
    Box(float width, float height, float length);
    Box(float width, float height, float length, int color[3]);
};
