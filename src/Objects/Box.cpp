#include "Box.h"

Box::Box()
{
    this->width = 1;
    this->height = 1;
    this->depth = 1;
    this->shape = ofBoxPrimitive(width, height, depth);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::gtx::pow2(width)+glm::gtx::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(width)));
    // DUPPLICATION 
    //this->inversedTenseurJ = ;
    RigidBody();
}

Box::Box(float width, float height, float length)
{
    this->width = width;
    this->height = height;
    this->depth = length;
    this->shape = ofBoxPrimitive(width, height, length);
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::gtx::pow2(width)+glm::gtx::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(width)));
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
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::gtx::pow2(width)+glm::gtx::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(width)));
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
    this->tenseurJ.l1 = Vector((getMass()/12)*(glm::gtx::pow2(width)+glm::gtx::pow2(height)),0,0);
    this->tenseurJ.l2 = Vector(0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(height)),0);
    this->tenseurJ.l3 = Vector(0,0,(getMass()/12)*(glm::gtx::pow2(depth)+glm::gtx::pow2(width)));
    RigidBody(_gravity, _linearVelocity, _angularVelocity, _linearAcceleration);
}
