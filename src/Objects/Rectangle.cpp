#include "Rectangle.h"

Rectangle::Rectangle()
{
    width = 0;
    height = 0;
    length = 0;
}

Rectangle::Rectangle(float width, float height, float length)
{
    this->width = width;
    this->height = height;
    this->length = length;
}

Rectangle::Rectangle(float width, float height, float length, int color[3])
{
    this->width = width;
    this->height = height;
    this->length = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
}
