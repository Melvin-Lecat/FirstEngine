#pragma once
#include "Shape.h"

class Box : public Shape
{
private:
    float width;
    float height;
    float depth;
    
public:
    Box();
    Box(float width, float height, float length);
    Box(float width, float height, float length, int color[3]);
    Box(float width, float height, float length, float _gravity, Vector _linearVelocity, Vector _angularVelocity,
        Vector _linearAcceleration, int color[3]);
    

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
    void draw()
    {
        ofSetColor(color[0], color[1], color[2]);
        shape.setPosition(position.v3());
        shape.setOrientation(orientation.q());
        shape.draw();
        ofSetColor(255, 255, 255);
    }
};
