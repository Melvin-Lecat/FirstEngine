#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
    float width;
    float height;
    float depth;

public:
    Box();
    Box(float width, float height, float length);
    Box(float width, float height, float length, int color[3]);
};
