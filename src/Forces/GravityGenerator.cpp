#include "GravityGenerator.h"

Vector GravityGenerator::getGravity()
{
    return gravity;
}

GravityGenerator::GravityGenerator(Vector gravity)
{
    this->gravity = gravity;
}

/**
 * @brief Update the object with a gravity force
 * 
 * @param object 
 * @param duration 
 */
void GravityGenerator::updateForce(RigidBody* object, float duration)
{
    if (object->getMass() == 0) return;
    object->addForce(this->gravity * object->getMass());
}
