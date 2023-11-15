#include "Box.h"

Box::Box()
{
    this->width = 1;
    this->height = 1;
    this->depth = 1;
    this->shape = ofBoxPrimitive(width, height, depth);
    RigidBody();
}

Box::Box(float width, float height, float length)
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->shape = ofBoxPrimitive(width, height, length);
    RigidBody();
}

Box::Box(float width, float height, float length, int color[3])
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofBoxPrimitive(width, height, length);
}

Box::Box(float width, float height, float length, float _gravity, Vector _linearVelocity, Vector _angularVelocity,
         Vector _linearAcceleration, int color[3])
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofBoxPrimitive(width, height, length);
    RigidBody(_gravity, _linearVelocity, _angularVelocity, _linearAcceleration);
}
