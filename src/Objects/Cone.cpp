#include "Cone.h"

Cone::Cone()
{
    this->radius = 1;
    this->height = 1;
    this->shape = ofConePrimitive(radius, height, 20, 20);
    this->tenseurJ.l1 = Vector((3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0,0);
    this->tenseurJ.l2 = Vector(0,(3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0);
    this->tenseurJ.l3 = Vector(0,0,(3*getMass()/10)*glm::pow2(radius));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody();
}

Cone::Cone(float radius, float height)
{
    this->radius = radius;
    this->height = height;
    this->shape = ofConePrimitive(radius, height, 20, 20);
    this->tenseurJ.l1 = Vector((3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0,0);
    this->tenseurJ.l2 = Vector(0,(3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0);
    this->tenseurJ.l3 = Vector(0,0,(3*getMass()/10)*glm::pow2(radius));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody();
}

Cone::Cone(float radius, float height, int color[3])
{
    this->radius = radius;
    this->height = height;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofConePrimitive(radius, height, 20, 20);
    this->tenseurJ.l1 = Vector((3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0,0);
    this->tenseurJ.l2 = Vector(0,(3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0);
    this->tenseurJ.l3 = Vector(0,0,(3*getMass()/10)*glm::pow2(radius));
    this->inversedTenseurJ = tenseurJ.inverse();
}

Cone::Cone(float radius, float height, float gravity, Vector linearVelocity, Vector angularVelocity,
         Vector linearAcceleration, int color[3])
{
    this->radius = radius;
    this->height = height;
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->shape = ofConePrimitive(radius, height, 20, 20);
    this->tenseurJ.l1 = Vector((3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0,0);
    this->tenseurJ.l2 = Vector(0,(3*getMass()/20)*(glm::pow2(radius)+glm::pow2(height)/4),0);
    this->tenseurJ.l3 = Vector(0,0,(3*getMass()/10)*glm::pow2(radius));
    this->inversedTenseurJ = tenseurJ.inverse();
    RigidBody(gravity, linearVelocity, angularVelocity, linearAcceleration);
}
void Cone::draw()
{
    // Draw the center of mass of the cone
    Vector realCenter = orientation.applyRotation(massCenter,orientation);
    ofSetColor(ofColor::yellow, 255);
    ofDrawSphere((position + realCenter).v3(), 5);

    // Draw the cone
    ofSetColor(color[0], color[1], color[2], 150);
    shape.setPosition(position.v3());
    shape.setOrientation(orientation.q());
    shape.draw();
    ofSetColor(255, 255, 255);
    
}