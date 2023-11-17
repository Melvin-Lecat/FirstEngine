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
    bool operator ==(Quaternion q);
    bool operator !=(Quaternion q);
    std::string to_string();

    // Methods
    Quaternion difference(Quaternion q);
    static Quaternion opposite(Quaternion q);
    static Quaternion toQuaternion(Vector v);
    glm::quat q();
    static Quaternion identity();
    float magnitude();
    Quaternion normalize();
    static Quaternion conjugate(Quaternion q);
    Quaternion inverse();
    float scalarProduct(Quaternion q);
    Vector applyRotation(Vector v, Quaternion q);
    Matrix quatToMat();
};
