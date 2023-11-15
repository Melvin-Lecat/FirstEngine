#pragma once
#include "RigidBody.h"
#include "Drawable.h"

class Rectangle : public RigidBody, public Drawable
{
    float width;
    float height;
    float length;

public:
    Rectangle();
    Rectangle(float width, float height, float length);
    Rectangle(float width, float height, float length, int color[3]);
    void draw() override;
};
