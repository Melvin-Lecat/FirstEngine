#include "Octree.h"

Octree::Octree(Vector position, float height, float width, float depth, float currentDepth): position(position),
    height(height), width(width), depth(depth), currentDepth(currentDepth), isLeaf(true)
{
    //cout << "Creating Octree" << endl;
    children[0] = children[1] = children[2] = children[3] = children[4] = children[5] = children[6]
        = children[7] = nullptr;
}

Octree::~Octree()
{
    //cout << "Destroying Octree" << endl;
}

void Octree::insert(RigidBody* object)
{
    if(!intersects(object)) {
        //cout << "Object out of bounds" << endl;
        return;
    }
    
    objects.push_back(object);

    if (objects.size() > MAX_OCTREE_SIZE)
    {
        // Subdivide tree
        if (currentDepth < MAX_OCTREE_DEPTH)
        {
            subdivide();
        }
    }
}


void Octree::subdivide()
{
    setupChildren(); // Setup Children if not already done

    if (children[0] ==nullptr){
        for (auto object : objects)
        {
            for (int i = 0; i < 8; i++) children[i]->insert(object);
        }
    }else
    {
        for (int i = 0; i < 8; i++) children[i]->insert(objects.back());
    }
}

void Octree::setupChildren()
{
    if(children[0] != nullptr) return; 

    auto halfHeight = height/2;
    auto halfWidth = width/2;
    auto halfDepth = depth/2;
    
    children[Quadrant1]=  new Octree(position + Vector(halfWidth, halfHeight, -halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant2]=  new Octree(position + Vector(-halfWidth, halfHeight, -halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant3]=  new Octree(position + Vector(halfWidth, halfHeight, halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant4]=  new Octree(position + Vector(-halfWidth, halfHeight, halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant5]=  new Octree(position + Vector(halfWidth, -halfHeight, -halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant6]=  new Octree(position + Vector(-halfWidth, -halfHeight, -halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant7]=  new Octree(position + Vector(halfWidth, -halfHeight, halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    children[Quadrant8]=  new Octree(position + Vector(-halfWidth, -halfHeight, halfDepth), halfHeight, halfWidth, halfDepth, currentDepth+1);
    isLeaf = false;

}

void Octree::clear()
{
    if(children[0] != nullptr){
        for (auto child: children)
        {
            child->clear();
            delete child;
        }
        children[0] = children[1] = children[2] = children[3] = children[4] = children[5] = children[6]
            = children[7] = nullptr;
    }
    for(int i = 0; i < objects.size(); i++) objects[i] = nullptr;
    objects.clear();
}

void Octree::update(RigidBody* object)
{
}

void Octree::draw()
{
    ofNoFill();
    ofSetColor(int(abs(position.x)) % 255, int(abs(position.y)) % 255, int(abs(position.z)) % 255);
    ofDrawBox(position.v3(), width*2, height*2, depth*2);
    if(!isLeaf){
        for (auto child: children)
        {
            if (child) child->draw();
        }
    }
    ofFill();
}

 std::vector<std::pair<RigidBody*,RigidBody*>> Octree::getCollisions()
{
    std::vector<std::pair<RigidBody*,RigidBody*>> collisions;
    if(children[0] == nullptr)
    {
        if(objects.size() == 2)
        {
            collisions.push_back(std::pair(objects[0],objects[1]));
            return collisions;   
        }
    }
    else
    {
        for (auto child: children)
        {
            auto childCollisions = child->getCollisions();
            for (auto collision: childCollisions)
            {
                collisions.emplace_back(collision);                
            }
            
        }   
    }
    return collisions;
}

bool Octree::intersects(RigidBody* object)
{
    if(abs(object->position.x - position.x) <= width && abs(object->position.y - position.y) <= height && abs(object->position.z - position.z) <= depth) return true;
    /*
    distance_x = Abs(sphere.x - boite.x) - boite.l / 2
    distance_y = Abs(sphere.y - boite.y) - boite.L / 2
    distance_z = Abs(sphere.z - boite.z) - boite.h / 2

    distance_x = Max(distance_x, 0)
    distance_y = Max(distance_y, 0)
    distance_z = Max(distance_z, 0)

    distance_spherique = sqrt(distance_x^2 + distance_y^2 + distance_z^2)

    Si distance_spherique <= sphere.r :
        Retourner Vrai
    Sinon :
        Retourner Faux
    */
    auto distance_x = abs(object->position.x - position.x) - width;
    auto distance_y = abs(object->position.y - position.y) - height;
    auto distance_z = abs(object->position.z - position.z) - depth;

    distance_x = max(distance_x, 0.0f);
    distance_y = max(distance_y, 0.0f);
    distance_z = max(distance_z, 0.0f);

    auto distance_spherique = sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);
    return distance_spherique <= 70;
    
}