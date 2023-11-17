#include "ForceRegistry.h"


void ForceRegistry::add(RigidBody* object, ForceGenerator* fg)
{
    struct ForceRegistration var;
    var.object = object;
    var.fg = fg;
    rg.push_back(var);
}

/**
 * Remove a object from the registry
 * @param object
 * @param forceGenerator
 */
void ForceRegistry::remove(RigidBody* object, ForceGenerator* forceGenerator)
{
    for (auto item = rg.begin(); item != rg.end();)
    {
        // Check if the object is out of the screen
        if (item->fg == forceGenerator && item->object == object)
        {
            // Remove the object from the list
            item = rg.erase(item);
        }
        else
        {
            // Else, go to the next object
            ++item;
        }
    }
}

/**
 * @brief Clear the registry
 */
void ForceRegistry::clear()
{
    rg.clear();
}

/**
 * @brief Update the forces of all the objects
 * 
 * @param duration 
 */
void ForceRegistry::updateForces(float duration)
{
    for (auto& var : rg)
    {
        var.fg->updateForce(var.object, duration);
    }
    clear();
}
