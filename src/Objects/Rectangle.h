#pragma once
#include "GameObject.h"

class Rectangle : GameObject
{
    float width;
    float height;
    float length;

public:
    Rectangle();
    Rectangle(float width, float height, float length);
    Rectangle(float width, float height, float length, int color[3]);
};
