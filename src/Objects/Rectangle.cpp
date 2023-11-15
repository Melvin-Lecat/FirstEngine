#include "Rectangle.h"

Rectangle::Rectangle()
{
    this->width = 1;
    this->height = 1;
    this->length = 1;
    this->shape = ofBoxPrimitive(width, height, length);
}

Rectangle::Rectangle(float width, float height, float length)
{
    this->width = width;
    this->height = height;
    this->length = length;
    this->shape = ofBoxPrimitive(width, height, length);
}

Rectangle::Rectangle(float width, float height, float length, int color[3])
{
    this->width = width;
    this->height = height;
    this->length = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofBoxPrimitive(width, height, length);
}

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
