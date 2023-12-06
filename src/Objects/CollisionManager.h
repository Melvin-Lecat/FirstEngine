#pragma once
#include <utility>

#include "Box.h"
#include "RigidBody.h"

class Octree;

class CollisionManager
{
public:
    static std::vector<std::pair<RigidBody*, RigidBody*>> getNarrowCollision(
    std::vector<std::pair<RigidBody*, RigidBody*>> collisions);
    static std::vector<Vector> getCorners(Box& box);
    static std::vector<Vector> getFaces(Box& box);
    static void resolveCollision(Vector applicationPoint, Vector n, float interpenetration, Box& first, Box& second);
    static bool intersect(Box& first, Box& second);
    static float getRadius(Vector n, Box box);

};
