#pragma once
#include "Shape.h"

class Box : public Shape
{
private:
    float width;
    float height;
    float depth;
    float colliderRadius = max(width, height, depth);
    
public:
    Box();
    Box(float width, float height, float length);
    Box(float width, float height, float length, int color[3]);
    Box(float width, float height, float length, Vector translation);
    Box(float width, float height, float length, float gravity, Vector linearVelocity, Vector angularVelocity,
        Vector linearAcceleration, int color[3]);
    void addForce(Vector force, Vector pointApplication);
    void addForce(Vector force);


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


/**
* @brief Draw the rectangle
*
*/
    void draw(); 
};
