#pragma once
#include "Drawable.h"
#include "RigidBody.h"

class Shape: public Drawable, public RigidBody
{
public:
    void draw() override {}
};
