#include "CollisionManager.h"

#include "Box.h"

std::vector<std::pair<RigidBody*, RigidBody*>> CollisionManager::getNarrowCollision(
    std::vector<std::pair<RigidBody*, RigidBody*>> collisions)
{
    std::vector<std::pair<RigidBody*, RigidBody*>> narrowCollisions;
    for (auto collision : collisions)
    {
        auto first = static_cast<Box*>(collision.first);
        auto second = static_cast<Box*>(collision.second);

        if (intersect(*first, *second))
        {
            narrowCollisions.emplace_back(std::pair(first,second));
        }
    }
    return narrowCollisions;
}

bool CollisionManager::intersect(Box& first, Box& second)
{
    Vector firstxAxis = Vector(first.shape.getXAxis().x, first.shape.getXAxis().y, first.shape.getXAxis().z).normalized();
    Vector firstyAxis = Vector(first.shape.getYAxis().x, first.shape.getYAxis().y, first.shape.getYAxis().z).normalized();
    Vector firstzAxis = Vector(first.shape.getZAxis().x, first.shape.getZAxis().y, first.shape.getZAxis().z).normalized();
    Vector secondxAxis = Vector(second.shape.getXAxis().x, second.shape.getXAxis().y, second.shape.getXAxis().z).normalized();
    Vector secondyAxis = Vector(second.shape.getYAxis().x, second.shape.getYAxis().y, second.shape.getYAxis().z).normalized();
    Vector secondzAxis = Vector(second.shape.getZAxis().x, second.shape.getZAxis().y, second.shape.getZAxis().z).normalized();
    auto list = std::vector<Vector>();
    list.push_back(firstxAxis);
    list.push_back(firstyAxis);
    list.push_back(firstzAxis);
    list.push_back(secondxAxis);
    list.push_back(secondyAxis);
    list.push_back(secondzAxis);

    auto dist = first.position - second.position;
    for (auto axis : list)
    {
        float firstRadius = getRadius(axis, first);
        float secondRadius = getRadius(axis, second);
        auto projectedDist = dist.projection(axis).magnitude();
        
        if (projectedDist > firstRadius + secondRadius)
        {
            return false;
        }
    }
    return true;
}

float CollisionManager::getRadius(Vector n, Box box)
{
    Vector xAxis = Vector(box.shape.getXAxis().x, box.shape.getXAxis().y, box.shape.getXAxis().z).
            normalized();
    Vector yAxis = Vector(box.shape.getYAxis().x, box.shape.getYAxis().y, box.shape.getYAxis().z).
        normalized();
    Vector zAxis = Vector(box.shape.getZAxis().x, box.shape.getZAxis().y, box.shape.getZAxis().z).
        normalized();
    
    // Position of the full positive diagonal
    Vector D1 = (xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2));

    Vector D2 = (xAxis * (-box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (-box.
        getDepth() / 2));

    // Position of the full positive diagonal
    Vector D3 = (xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (-box.
        getDepth() / 2));

    // Position of the full negative diagonal
    Vector D4 = (xAxis * (-box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2));

    Vector projectedPosition = box.position.projection(n);
    auto radius = max(D1.projection(n).magnitude(), D2.projection(n).magnitude());
    radius = max(radius, D3.projection(n).magnitude());
    radius = max(radius, D4.projection(n).magnitude());
    return radius;

}