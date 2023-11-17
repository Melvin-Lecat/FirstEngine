#include "FrictionGenerator.h"

FrictionGenerator::FrictionGenerator(float k1)
{
    this->k1 = k1;
}

/**
 * @brief Update the particle with a friction force
 * 
 * @param object 
 * @param duration 
 */
void FrictionGenerator::updateForce(RigidBody* object, float duration)
{
    object->addForce(object->linearVelocity * (-k1));
}