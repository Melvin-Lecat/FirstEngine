#pragma once
#include <ofMain.h>
#include "Vector.h"

class Matrix4x4
{
public:
    Vector l1, l2, l3, l4;

    Matrix4x4(Vector v1, Vector v2, Vector v3);
    Matrix4x4(Vector v1, Vector v2, Vector v3, Vector v4);

    Matrix4x4 operator +(Matrix4x4 m);
    Matrix4x4 operator +=(Matrix4x4 m);
    Matrix4x4 operator -(Matrix4x4 m);
    Matrix4x4 operator -=(Matrix4x4 m);
    // Scalar product
    Matrix4x4 operator *(Matrix4x4 m);
    Matrix4x4 operator *=(Matrix4x4 m);
    // Multiplication by scalar
    Matrix4x4 operator *(float k);
    Matrix4x4 operator *=(float k);

    bool operator ==(Matrix4x4 m);
    bool operator !=(Matrix4x4 m);
    std::string to_string();
    
    static Matrix4x4 zero();
    float determinant();
    Matrix4x4 transpose();
};
