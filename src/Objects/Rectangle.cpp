#pragma once
#include "RigidBody.h"

class Rectangle : public RigidBody
{
    float width;
    float height;
    float length;

public:
    Rectangle();
    Rectangle(float width, float height, float length);
    Rectangle(float width, float height, float length, int color[3]);
};

/**
 * @brief Draw the rectangle
 *
 */
void Rectangle::draw()
{
    ofSetColor(color[0], color[1], color[2]);
    Vector realPos = Vector(position.x, ofGetHeight() - position.y);
    ofDrawRectangle(realPos.v2(), width, length);
    ofSetColor(255, 255, 255);
}
