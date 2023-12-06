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
    static bool intersect(Box& first, Box& second);
    static float getRadius(Vector n, Box box);

};
