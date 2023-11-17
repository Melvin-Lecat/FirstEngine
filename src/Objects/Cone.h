#pragma once
#include "RigidBody.h"

class Cone : public RigidBody
{
private:
    float radius;
    float height;
    
public:
    Cone();
    Cone(float radius, float height);
    Cone(float radius, float height, int color[3]);
    Cone(float radius, float height, float _gravity, Vector _linearVelocity, Vector _angularVelocity,
        Vector _linearAcceleration, int color[3]);
    
    

    float getRadius()
    {
        return radius;
    }

    float getHeight()
    {
        return height;
    }

    /**
* @brief Draw the cone
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
