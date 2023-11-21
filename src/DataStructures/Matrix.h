#pragma once
#include <ofMain.h>

#include "Vector.h"
#include "Matrix4x4.h"

class Matrix
{
public:
    Vector l1;
    Vector l2;
    Vector l3;

    Matrix(Vector v1, Vector v2, Vector v3);

    Matrix operator +(Matrix m);
    Matrix operator +=(Matrix m);
    Matrix operator -(Matrix m);
    Matrix operator -=(Matrix m);
    // Matrix product
    Matrix operator *(Matrix m);
    Matrix operator *=(Matrix m);
    // Multiplication by scalar
    Matrix operator *(float k);
    Matrix operator *=(float k);
    // Multiplication by vector
    Vector operator *(Vector v);

    bool operator ==(Matrix m);
    bool operator !=(Matrix m);
    std::string to_string();

    static Matrix zero();
    Matrix inverse();
    Matrix transpose();
    float determinant();
    
};
