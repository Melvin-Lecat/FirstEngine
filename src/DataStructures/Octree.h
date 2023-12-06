#pragma once
#include "RigidBody.h"
#include "Vector.h"

#define MAX_OCTREE_DEPTH 4
#define MAX_OCTREE_SIZE 2

enum  OctreePosition
{
    Quadrant1 = 0,
    Quadrant2 = 1,
    Quadrant3 = 2,
    Quadrant4 = 3,
    Quadrant5 = 4,
    Quadrant6 = 5,
    Quadrant7 = 6,
    Quadrant8 = 7
};

class Octree
{
    int debugValue = 0;
private: 
    Vector position;
    float height, width, depth;
    float currentDepth; 
    Octree* children[8];
    std::vector<RigidBody*> objects;
    bool isLeaf;

    
    
    
public:
    Octree(Vector position, float height, float width, float depth, float currentDepth);
    ~Octree();

    void insert(RigidBody* object);
    void remove(RigidBody* object);
    void subdivide();  
    void setupChildren();  
    void clear();
    void update(RigidBody* object);
    void draw(bool printTree, std::string tab);

    std::vector<std::pair<RigidBody*,RigidBody*>> getCollisions();

    bool intersects(RigidBody* object);
};
