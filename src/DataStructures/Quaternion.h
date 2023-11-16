#pragma once
#include <ofMain.h>
#include "Vector.h"
#include "Matrix.h"

class Quaternion
{
public:
    float w, x, y, z;
    
    Quaternion(float w, float x, float y, float z);
    Quaternion(float angle, Vector n);

    Quaternion operator /(float k);
    Quaternion operator *(float val);
    Quaternion operator *(Quaternion q);
    Quaternion operator +(Quaternion q);
    Quaternion operator -(Quaternion q);
    std::string to_string();

    // Methods
    static Quaternion opposite(Quaternion q);
    static Quaternion toQuaternion(Vector v);
    glm::quat q();
    static Quaternion identity();
    float magnitude();
    Quaternion normalize();
    static Quaternion conjugate(Quaternion q);
    Quaternion inverse(Quaternion q);
    float scalarProduct(Quaternion q);
    Vector applyRotation(Vector v, Quaternion q);
    Matrix quatToMat();
    // Quaternion slerp(Quaternion q1, Quaternion q2, float t);
};
