#pragma once
#include "Drawable.h"
#include "RigidBody.h"

class Rectangle : public RigidBody, public Drawable
{
    float width;
    float height;
    float length;

public:
    Rectangle();
    Rectangle(float width, float height, float length);
    Rectangle(float width, float height, float length, int color[3]);

};


