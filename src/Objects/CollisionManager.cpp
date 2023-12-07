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

        if (intersect(*first, *second) || intersect(*second, *first))
        {
            narrowCollisions.emplace_back(std::pair(first,second));
        }
    }
    return narrowCollisions;
}

 std::vector<Vector> CollisionManager::getCorners(Box& box)
{
    Vector xAxis = Vector(box.shape.getXAxis().x, box.shape.getXAxis().y, box.shape.getXAxis().z).normalized();
    Vector yAxis = Vector(box.shape.getYAxis().x, box.shape.getYAxis().y, box.shape.getYAxis().z).normalized();
    Vector zAxis = Vector(box.shape.getZAxis().x, box.shape.getZAxis().y, box.shape.getZAxis().z).normalized();
    //  Retrieve the 8 corners of the box
    Vector Corner1 = box.position + xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2);
    Vector Corner2 = box.position - xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2);
    Vector Corner3 = box.position + xAxis * (box.getWidth() / 2) - yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2);
    Vector Corner4 = box.position - xAxis * (box.getWidth() / 2) - yAxis * (box.getHeight() / 2) + zAxis * (box.
        getDepth() / 2);
    Vector Corner5 = box.position + xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) - zAxis * (box.
        getDepth() / 2);
    Vector Corner6 = box.position - xAxis * (box.getWidth() / 2) + yAxis * (box.getHeight() / 2) - zAxis * (box.
        getDepth() / 2);
    Vector Corner7 = box.position + xAxis * (box.getWidth() / 2) - yAxis * (box.getHeight() / 2) - zAxis * (box.
        getDepth() / 2);
    Vector Corner8 = box.position - xAxis * (box.getWidth() / 2) - yAxis * (box.getHeight() / 2) - zAxis * (box.
        getDepth() / 2);

    auto cornerList = std::vector<Vector>();
    cornerList.push_back(Corner1);
    cornerList.push_back(Corner2);
    cornerList.push_back(Corner3);
    cornerList.push_back(Corner4);
    cornerList.push_back(Corner5);
    cornerList.push_back(Corner6);
    cornerList.push_back(Corner7);
    cornerList.push_back(Corner8);
    return cornerList;
}

 std::vector<Vector> CollisionManager::getFaces(Box& box)
{
    // Retrieve the 6 faces of second
    Vector face1 = box.position + Vector(box.shape.getXAxis().x, box.shape.getXAxis().y, box.shape.getXAxis().z).normalized()*(box.getWidth()/2);  
    Vector face2 = box.position + Vector(box.shape.getYAxis().x, box.shape.getYAxis().y, box.shape.getYAxis().z).normalized()*(box.getHeight()/2);
    Vector face3 = box.position + Vector(box.shape.getZAxis().x, box.shape.getZAxis().y, box.shape.getZAxis().z).normalized()*(box.getDepth()/2);
    Vector face4 = box.position - Vector(box.shape.getXAxis().x, box.shape.getXAxis().y, box.shape.getXAxis().z).normalized()*(box.getWidth()/2) ;
    Vector face5 = box.position - Vector(box.shape.getYAxis().x, box.shape.getYAxis().y, box.shape.getYAxis().z).normalized()*(box.getHeight()/2);
    Vector face6 = box.position - Vector(box.shape.getZAxis().x, box.shape.getZAxis().y, box.shape.getZAxis().z).normalized()*(box.getDepth()/2);

    auto faceList = std::vector<Vector>();
    faceList.push_back(face1);
    faceList.push_back(face2);
    faceList.push_back(face3);
    faceList.push_back(face4);
    faceList.push_back(face5);
    faceList.push_back(face6);
    return faceList;
}

void CollisionManager::resolveCollision(Vector applicationPoint, Vector n, float interpenetration,  Box& first, Box& second)
{

    // Resolve the position
    float K = first.getMass() / ( first.getMass() + second.getMass());
    auto f= n * K * interpenetration;
    first.position += n * K * interpenetration;
    
    // Apply the force
    float intensity = ((first.linearVelocity.magnitude() > first.angularVelocity.magnitude() )? first.linearVelocity : first.angularVelocity).magnitude();
    Vector force = n* (0.9*intensity/(ofGetLastFrameTime() == 0.0f ? 1.0f/60.0f: ofGetLastFrameTime()));
    first.addForce(force, applicationPoint);
}

// Check if first intersects with second. Return true if it does
bool CollisionManager::intersect(Box& first, Box& second)
{
    auto corners = getCorners(first);

    auto faces = getFaces(second);

    Vector cornerPoint;
    bool intersected = true; 
    for (auto corner : corners)
    {
        intersected = true;
        for (auto face : faces)
        {
            auto relativeCorner = corner - face;
            
            // cout << "Corner: " << relativeCorner * face <<  endl;
            if(relativeCorner * face > 0)
            {
                intersected = false;
                break;
            }
            
        }
        if(intersected)
        {
            cornerPoint = corner;
            break;
        }
        //cout << "=====================================================" << endl;
    }


    if (intersected){
        float min = FLT_MAX;
        Vector n = faces[0];
        cout << "==================" << endl;
        cout << "Corner: " << cornerPoint.v3() << endl;
        for(auto face : faces )
        {
            auto relativeDistance = (cornerPoint).projection(face).distance(face);
            
            //auto relativeDistance = (cornerPoint - face).projection(face).magnitude();
            cout << "Relative distance: " << relativeDistance << endl;
            
            if(relativeDistance < min)
            {
                n = face.normalized();
                min = relativeDistance;
            }
        }
        cout << "Min: " << min << endl;

        cout << "============================" << endl;
        auto Copy = first.copy();
        resolveCollision(cornerPoint,n.opposite(), min,first, second);
        resolveCollision(cornerPoint,n, min,second, *Copy);
    }
    
    return intersected;
}
/*
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

}*/