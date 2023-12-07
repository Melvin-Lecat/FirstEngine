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

/**
 * @brief: Inserts an object into the tree
 * @param object: The object to insert
 */
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

/**
 * @brief: Handles the tree's subdivision when the object vector is full (objects.size() > MAX_OCTREE_SIZE)
 */

void Octree::subdivide()
{
    setupChildren(); // Setup Children if not already done

    if (children[0] !=nullptr){
        for (auto object : objects)
        {
            for (int i = 0; i < 8; i++) children[i]->insert(object);
        }
    }else
    {
        for (int i = 0; i < 8; i++) children[i]->insert(objects.back());
    }
}

/**
 * @brief : Initializes the children nodes if not already done.  
 */
void Octree::setupChildren()
{
    debugValue ++;
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

/**
 * @brief: Deletes and frees the children nodes and object vector
 */
void Octree::clear()
{
    debugValue = 0;
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

/**
 * @brief 
 * @param printTree: Boolean value to enable/disable the tree printing in CLI 
 * @param tab: If printTree is true, this is the string that will be printed at the beggining of each line (It should always be "") 
 */
void Octree::draw(bool printTree, std::string tab = "")
{
    if (printTree) cout << tab << "Depth " << currentDepth << " Size "<< objects.size() << " check " << debugValue << endl;
    ofNoFill();
    //ofSetColor(int(abs(position.x)) % 255, int(abs(position.y)) % 255, int(abs(position.z)) % 255);
    ofSetColor(ofColor::red);
    ofDrawBox(position.v3(), width*2, height*2, depth*2);
    if(!isLeaf){
        for (auto child: children)
        {
            if (child) child->draw(printTree,tab+"\t");
        }
    }
    ofFill();

}

/**
 * @brief: Handler function to check for broad collisions 
 * @return: Contains all objects that collide
 */
std::vector<std::pair<RigidBody*,RigidBody*>> Octree::getCollisions()
{
    std::vector<std::pair<RigidBody*,RigidBody*>> collisions;
    if(children[0] == nullptr)
    {
        if(objects.size() == 2)
        {
            if(objects[0]->colliderRadius + objects[1]->colliderRadius > objects[0]->position.distance(objects[1]->position)){
                collisions.push_back(std::pair(objects[0],objects[1]));
                return collisions;
            } 
        }else if(objects.size() > 2)
        {
            for (int i = 0; i < static_cast<int>(objects.size())-1; i++)
            {
                for (int j = i+1; j < static_cast<int>(objects.size()); j++)
                {
                    if(objects[i]->colliderRadius + objects[j]->colliderRadius > objects[i]->position.distance(objects[j]->position)){
                        collisions.push_back(std::pair(objects[i],objects[j]));
                    } 
                }
            }
            
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
                if(!ofContains(collisions, collision))
                    collisions.emplace_back(collision);                
            }
            
        }   
    }
    return collisions;
}

/**
 * @brief: Handler function to check if a Rigidbody overlaps with the subdivision
 * @param object: The object to check with
 * @return: Returns true if the object overlaps with the subdivision
 */
bool Octree::intersects(RigidBody* object)
{
    // Checks if the object is inside the subdivision
    if(abs(object->position.x - position.x) <= width && abs(object->position.y - position.y) <= height && abs(object->position.z - position.z) <= depth) return true;
    
    // Else it checks if the object bounding sphere overlaps with the subdivision
    auto distance_x = abs(object->position.x - position.x) - width;
    auto distance_y = abs(object->position.y - position.y) - height;
    auto distance_z = abs(object->position.z - position.z) - depth;

    distance_x = max(distance_x, 0.0f);
    distance_y = max(distance_y, 0.0f);
    distance_z = max(distance_z, 0.0f);

    auto distance_spherique = sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);
    return distance_spherique <= object->colliderRadius;
    
}