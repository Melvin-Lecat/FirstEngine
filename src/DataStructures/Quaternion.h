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
    //passage quaternion vers matrice 4x4

    // Methods
    Quaternion negation(Quaternion q);
    Quaternion identitePos();
    Quaternion identiteNeg();
    float norme(Quaternion q);
    Quaternion conjugue(Quaternion q);
    Quaternion inverse(Quaternion q);
    Quaternion multiplication(Quaternion q1, Quaternion q2);
    // Avec un point Quaternion multiplication(Quaternion q1, Quaternion q2);
    Quaternion difference(Quaternion q1, Quaternion q2);
    float produitScalaire(Quaternion q1, Quaternion q2);
    //Quaternion slerp(Quaternion q1, Quaternion q2, float t);
    Vector applyRotation(Vector v, Quaternion q);
    Matrix quatToMat();
    Quaternion operator *(float val);

    Quaternion operator /(float k);
    Quaternion operator +(Quaternion q);
    static Quaternion toQuaternion(Vector v);
    std::string to_string();
    glm::quat q();
};
