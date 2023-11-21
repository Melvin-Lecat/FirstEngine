#include "Matrix.h"

Matrix::Matrix(Vector v1, Vector v2, Vector v3)
{
    this->l1 = v1;
    this->l2 = v2;
    this->l3 = v3;
}

Matrix Matrix::operator +(Matrix m)
{
    return Matrix(this->l1 + m.l1, this->l2 + m.l2, this->l3 + m.l3);
}

Matrix Matrix::operator +=(Matrix m)
{
    return Matrix(this->l1 + m.l1, this->l2 + m.l2, this->l3 + m.l3);
}

Matrix Matrix::operator -(Matrix m)
{
    return Matrix(this->l1 - m.l1, this->l2 - m.l2, this->l3 - m.l3);
}

Matrix Matrix::operator -=(Matrix m)
{
    return Matrix(this->l1 - m.l1, this->l2 - m.l2, this->l3 - m.l3);
}

Matrix Matrix::operator *(Matrix m)
{
    return Matrix(Vector((this->l1.x * m.l1.x) + (this->l1.y * m.l2.x) + (this->l1.z * m.l3.x),
                         (this->l1.x * m.l1.y) + (this->l1.y * m.l2.y) + (this->l1.z * m.l3.y),
                         (this->l1.x * m.l1.z) + (this->l1.y * m.l2.z) + (this->l1.z * m.l3.z)),
                  Vector((this->l2.x * m.l1.x) + (this->l2.y * m.l2.x) + (this->l2.z * m.l3.x),
                         (this->l2.x * m.l1.y) + (this->l2.y * m.l2.y) + (this->l2.z * m.l3.y),
                         (this->l2.x * m.l1.z) + (this->l2.y * m.l2.z) + (this->l2.z * m.l3.z)),
                  Vector((this->l3.x * m.l1.x) + (this->l3.y * m.l2.x) + (this->l3.z * m.l3.x),
                         (this->l3.x * m.l1.y) + (this->l3.y * m.l2.y) + (this->l3.z * m.l3.y),
                         (this->l3.x * m.l1.z) + (this->l3.y * m.l2.z) + (this->l3.z * m.l3.z)));
}

Matrix Matrix::operator *=(Matrix m)
{
    return Matrix(Vector((this->l1.x * m.l1.x) + (this->l1.y * m.l2.x) + (this->l1.z * m.l3.x),
                         (this->l1.x * m.l1.y) + (this->l1.y * m.l2.y) + (this->l1.z * m.l3.y),
                         (this->l1.x * m.l1.z) + (this->l1.y * m.l2.z) + (this->l1.z * m.l3.z)),
                  Vector((this->l2.x * m.l1.x) + (this->l2.y * m.l2.x) + (this->l2.z * m.l3.x),
                         (this->l2.x * m.l1.y) + (this->l2.y * m.l2.y) + (this->l2.z * m.l3.y),
                         (this->l2.x * m.l1.z) + (this->l2.y * m.l2.z) + (this->l2.z * m.l3.z)),
                  Vector((this->l3.x * m.l1.x) + (this->l3.y * m.l2.x) + (this->l3.z * m.l3.x),
                         (this->l3.x * m.l1.y) + (this->l3.y * m.l2.y) + (this->l3.z * m.l3.y),
                         (this->l3.x * m.l1.z) + (this->l3.y * m.l2.z) + (this->l3.z * m.l3.z)));
}

Matrix Matrix::operator *(float k)
{
    return Matrix(this->l1 * k, this->l2 * k, this->l3 * k);
}

Matrix Matrix::operator *=(float k)
{
    return Matrix(this->l1 * k, this->l2 * k, this->l3 * k);
}

Vector Matrix::operator *(Vector v)
{
    return Vector(v.x*this->l1.x + v.y*this->l1.y + v.z*this->l1.z + v.w*this->l1.w, v.x*this->l2.x + v.y*this->l2.y + v.z*this->l2.z + v.w*this->l2.w, v.x*this->l3.x + v.y*this->l3.y + v.z*this->l3.z + v.w*this->l3.w, v.w);
}

Vector Matrix::operator *=(Vector v)
{
    return Vector(v.x*this->l1.x + v.y*this->l1.y + v.z*this->l1.z + v.w*this->l1.w, v.x*this->l2.x + v.y*this->l2.y + v.z*this->l2.z + v.w*this->l2.w, v.x*this->l3.x + v.y*this->l3.y + v.z*this->l3.z + v.w*this->l3.w, v.w);
}

bool Matrix::operator ==(Matrix m)
{
    return this->l1 == m.l1 && this->l2 == m.l2 && this->l3 == m.l3;
}

bool Matrix::operator !=(Matrix m)
{
    return this->l1 != m.l1 || this->l2 != m.l2 || this->l3 != m.l3;
}

std::string Matrix::to_string()
{
    std::stringstream ss;
    int s = 5;

    ss << "| " << std::setw(s) << l1.x << " " << std::setw(s) << l2.x << " " << std::setw(s) << l3.x << " |" << std::endl;
    ss << "| " << std::setw(s) << l1.y << " " << std::setw(s) << l2.y << " " << std::setw(s) << l3.y << " |" << std::endl;
    ss << "| " << std::setw(s) << l1.z << " " << std::setw(s) << l2.z << " " << std::setw(s) << l3.z << " |" << std::endl;

    return ss.str();
}

Matrix Matrix::zero() { return Matrix(Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0)); }

/**
 * @brief Compute the inverse of the matrix
 * 
 * @return The inverse of the matrix if it exists or throw an error if it doesn't
 */
Matrix Matrix::inverse()
{
    float det = l1.x * (l2.y * l3.z - l2.z * l3.y) - l1.y * (l2.x * l3.z - l2.z * l3.x) + l1.z * (l2.x * l3.y - l2.y * l3.x);

    if (det == 0)
    {
        throw std::runtime_error("Matrix is not invertible (determinant is zero).");
    }
    
    Vector v1(l2.y * l3.z - l2.z * l3.y, l1.z * l3.y - l1.y * l3.z, l1.y * l2.z - l1.z * l2.y);
    Vector v2(l2.z * l3.x - l2.x * l3.z, l1.x * l3.z - l1.z * l3.x, l1.z * l2.x - l1.x * l2.z);
    Vector v3(l2.x * l3.y - l2.y * l3.x, l1.y * l3.x - l1.x * l3.y, l1.x * l2.y - l1.y * l2.x);

    Matrix adjoint(v1, v2, v3);

    float invDet = 1.0f / det;
    Matrix inverseMatrix = adjoint * invDet;

    return inverseMatrix;
}

Matrix Matrix::transpose()
{
    return Matrix(Vector(this->l1.x, this->l2.x, this->l3.x), Vector(this->l1.y, this->l2.y, this->l3.y), Vector(this->l1.z, this->l2.z, this->l3.z));
}

float Matrix::determinant()
{
    return (this->l1.x * this->l2.y * this->l3.z + this->l2.x * this->l3.y * this->l1.z + this->l3.x * this->l1.y * this->l2.z - this->l3.x * this->l2.y * this->l1.z - this->l2.x * this->l1.y * this->l3.z - this->l1.x * this->l3.y * this->l2.z);
}