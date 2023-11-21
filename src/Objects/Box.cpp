#include "Box.h"

Box::Box()
{
    this->width = 1;// b
    this->height = 1; // c
    this->depth = 1;// a
    this->shape = ofBoxPrimitive(width, height, depth);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::pow2(width)+glm::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(width)));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody();
}

Box::Box(float width, float height, float length)
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->shape = ofBoxPrimitive(width, height, length);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::pow2(width)+glm::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(width)));
    this->inversedTenseurJ = tenseurJ.inverse();
    massCenter = Vector(0,0,0);
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
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::pow2(width)+glm::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(width)));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody();
}
Box::Box(float width, float height, float length, Vector translation)
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofBoxPrimitive(width, height, length);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::pow2(width)+glm::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(width)));
    this->moveCenterMass(translation);
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody();
}

Box::Box(float width, float height, float length, float gravity, Vector linearVelocity, Vector angularVelocity,
         Vector linearAcceleration, int color[3])
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofBoxPrimitive(width, height, length);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::pow2(width)+glm::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::pow2(depth)+glm::pow2(width)));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody(gravity, linearVelocity, angularVelocity, linearAcceleration);
}

void Box::addForce(Vector force, Vector pointApplication)
{
   /*auto xAxis= shape.getXAxis();
    auto yAxis = shape.getYAxis();
    auto zAxis = shape.getZAxis();
    auto xVal = pointApplication.projection(Vector(xAxis.x, xAxis.y, xAxis.z)).x;
    auto yVal = pointApplication.projection(Vector(yAxis.x, yAxis.y, yAxis.z)).y;
    auto zVal = pointApplication.projection(Vector(zAxis.x, zAxis.y, zAxis.z)).z;
    glm::clamp(xVal, -depth/2, depth/2); // x = depth , y = width , z = height
    glm::clamp(yVal, -width/2, width/2);
    glm::clamp(zVal, -height/2, height/2);
    auto correctedPoint = Vector(xVal, yVal, zVal);*/
    RigidBody::addForce(force, pointApplication);
}
void Box::addForce(Vector force)
{
    RigidBody::addForce(force);
}

void Box::draw()
{
    // Draw the center of mass of the box
    Vector realCenter = orientation.applyRotation(massCenter,orientation);
    ofSetColor(ofColor::yellow, 255);
    ofDrawSphere((position + realCenter).v3(), 5);

    // Draw the box
    ofSetColor(color[0], color[1], color[2], 150);
    shape.setPosition(position.v3());
    shape.setOrientation(orientation.q());
    shape.draw();
    ofSetColor(255, 255, 255);
    
}
