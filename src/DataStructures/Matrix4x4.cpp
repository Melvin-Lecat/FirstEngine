#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(Vector v1, Vector v2, Vector v3)
{
    this->l1 = v1;
    this->l2 = v2;
    this->l3 = v3;
    this->l4 = Vector(0, 0, 0, 1);
}

Matrix4x4::Matrix4x4(Vector v1, Vector v2, Vector v3, Vector v4)
{
    this->l1 = v1;
    this->l2 = v2;
    this->l3 = v3;
    this->l4 = v4;
}

Matrix4x4 Matrix4x4::operator +(Matrix4x4 m)
{
    return Matrix4x4(this->l1 + m.l1, this->l2 + m.l2, this->l3 + m.l3, this->l4 + m.l4);
}

Matrix4x4 Matrix4x4::operator +=(Matrix4x4 m)
{
    return Matrix4x4(this->l1 += m.l1, this->l2 += m.l2, this->l3 += m.l3, this->l4 += m.l4);
}

Matrix4x4 Matrix4x4::operator -(Matrix4x4 m)
{
    return Matrix4x4(this->l1 - m.l1, this->l2 - m.l2, this->l3 - m.l3, this->l4 - m.l4);
}

Matrix4x4 Matrix4x4::operator -=(Matrix4x4 m)
{
    return Matrix4x4(this->l1 -= m.l1, this->l2 -= m.l2, this->l3 -= m.l3, this->l4 -= m.l4);
}

Matrix4x4 Matrix4x4::operator *(Matrix4x4 m)
{
    return Matrix4x4(
        Vector((this->l1.x * m.l1.x) + (this->l1.y * m.l2.x) + (this->l1.z * m.l3.x) + (this->l1.w * m.l4.x),
               (this->l1.x * m.l1.y) + (this->l1.y * m.l2.y) + (this->l1.z * m.l3.y) + (this->l1.w * m.l4.y),
               (this->l1.x * m.l1.z) + (this->l1.y * m.l2.z) + (this->l1.z * m.l3.z) + (this->l1.w * m.l4.z),
               (this->l1.x * m.l1.w) + (this->l1.y * m.l2.w) + (this->l1.z * m.l3.w) + (this->l1.w * m.l4.w)),
        Vector((this->l2.x * m.l1.x) + (this->l2.y * m.l2.x) + (this->l2.z * m.l3.x) + (this->l2.w * m.l4.x),
               (this->l2.x * m.l1.y) + (this->l2.y * m.l2.y) + (this->l2.z * m.l3.y) + (this->l2.w * m.l4.y),
               (this->l2.x * m.l1.z) + (this->l2.y * m.l2.z) + (this->l2.z * m.l3.z) + (this->l2.w * m.l4.z),
               (this->l2.x * m.l1.w) + (this->l2.y * m.l2.w) + (this->l2.z * m.l3.w) + (this->l2.w * m.l4.w)),
        Vector((this->l3.x * m.l1.x) + (this->l3.y * m.l2.x) + (this->l3.z * m.l3.x) + (this->l3.w * m.l4.x),
               (this->l3.x * m.l1.y) + (this->l3.y * m.l2.y) + (this->l3.z * m.l3.y) + (this->l3.w * m.l4.y),
               (this->l3.x * m.l1.z) + (this->l3.y * m.l2.z) + (this->l3.z * m.l3.z) + (this->l3.w * m.l4.z),
               (this->l3.x * m.l1.w) + (this->l3.y * m.l2.w) + (this->l3.z * m.l3.w) + (this->l3.w * m.l4.w)),
        Vector((this->l4.x * m.l1.x) + (this->l4.y * m.l2.x) + (this->l4.z * m.l3.x) + (this->l4.w * m.l4.x),
               (this->l4.x * m.l1.y) + (this->l4.y * m.l2.y) + (this->l4.z * m.l3.y) + (this->l4.w * m.l4.y),
               (this->l4.x * m.l1.z) + (this->l4.y * m.l2.z) + (this->l4.z * m.l3.z) + (this->l4.w * m.l4.z),
               (this->l4.x * m.l1.w) + (this->l4.y * m.l2.w) + (this->l4.z * m.l3.w) + (this->l4.w * m.l4.w)));
}

Matrix4x4 Matrix4x4::operator *=(Matrix4x4 m)
{
    return Matrix4x4(
        Vector((this->l1.x *= m.l1.x) + (this->l1.y *= m.l2.x) + (this->l1.z *= m.l3.x) + (this->l1.w *= m.l4.x),
               (this->l1.x *= m.l1.y) + (this->l1.y *= m.l2.y) + (this->l1.z *= m.l3.y) + (this->l1.w *= m.l4.y),
               (this->l1.x *= m.l1.z) + (this->l1.y *= m.l2.z) + (this->l1.z *= m.l3.z) + (this->l1.w *= m.l4.z),
               (this->l1.x *= m.l1.w) + (this->l1.y *= m.l2.w) + (this->l1.z *= m.l3.w) + (this->l1.w *= m.l4.w)),
        Vector((this->l2.x *= m.l1.x) + (this->l2.y *= m.l2.x) + (this->l2.z *= m.l3.x) + (this->l2.w *= m.l4.x),
               (this->l2.x *= m.l1.y) + (this->l2.y *= m.l2.y) + (this->l2.z *= m.l3.y) + (this->l2.w *= m.l4.y),
               (this->l2.x *= m.l1.z) + (this->l2.y *= m.l2.z) + (this->l2.z *= m.l3.z) + (this->l2.w *= m.l4.z),
               (this->l2.x *= m.l1.w) + (this->l2.y *= m.l2.w) + (this->l2.z *= m.l3.w) + (this->l2.w *= m.l4.w)),
        Vector((this->l3.x *= m.l1.x) + (this->l3.y *= m.l2.x) + (this->l3.z *= m.l3.x) + (this->l3.w *= m.l4.x),
               (this->l3.x *= m.l1.y) + (this->l3.y *= m.l2.y) + (this->l3.z *= m.l3.y) + (this->l3.w *= m.l4.y),
               (this->l3.x *= m.l1.z) + (this->l3.y *= m.l2.z) + (this->l3.z *= m.l3.z) + (this->l3.w *= m.l4.z),
               (this->l3.x *= m.l1.w) + (this->l3.y *= m.l2.w) + (this->l3.z *= m.l3.w) + (this->l3.w *= m.l4.w)),
        Vector((this->l4.x *= m.l1.x) + (this->l4.y *= m.l2.x) + (this->l4.z *= m.l3.x) + (this->l4.w *= m.l4.x),
               (this->l4.x *= m.l1.y) + (this->l4.y *= m.l2.y) + (this->l4.z *= m.l3.y) + (this->l4.w *= m.l4.y),
               (this->l4.x *= m.l1.z) + (this->l4.y *= m.l2.z) + (this->l4.z *= m.l3.z) + (this->l4.w *= m.l4.z),
               (this->l4.x *= m.l1.w) + (this->l4.y *= m.l2.w) + (this->l4.z *= m.l3.w) + (this->l4.w *= m.l4.w)));
}

Matrix4x4 Matrix4x4::operator *(float k)
{
    return Matrix4x4(this->l1 * k, this->l2 * k, this->l3 * k, this->l4 * k);
}

Matrix4x4 Matrix4x4::operator *=(float k)
{
    return Matrix4x4(this->l1 *= k, this->l2 *= k, this->l3 *= k, this->l4 *= k);
}

Vector Matrix4x4::operator *(Vector v)
{
    return Vector(v.x * this->l1.x + v.y * this->l1.y + v.z * this->l1.z + v.w * this->l1.w, v.x * this->l2.x + v.y * this->l2.y + v.z * this->l2.z + v.w * this->l2.w, v.x * this->l3.x + v.y * this->l3.y + v.z * this->l3.z + v.w * this->l3.w, v.x * this->l4.x + v.y * this->l4.y + v.z * this->l4.z + v.w * this->l4.w);
}

Vector Matrix4x4::operator *=(Vector v)
{
    return Vector(v.x * this->l1.x + v.y * this->l1.y + v.z * this->l1.z + v.w * this->l1.w, v.x * this->l2.x + v.y * this->l2.y + v.z * this->l2.z + v.w * this->l2.w, v.x * this->l3.x + v.y * this->l3.y + v.z * this->l3.z + v.w * this->l3.w, v.x * this->l4.x + v.y * this->l4.y + v.z * this->l4.z + v.w * this->l4.w);
}

/**
 * @brief Compute the inverse of the matrix
 *
 * @return The inverse of the matrix if it exists or throw an error if it doesn't
 */
Matrix4x4 Matrix4x4::inverse()
{
    float det = determinant();

    if (det == 0)
    {
        throw std::runtime_error("Matrix is not invertible (determinant is zero).");
    }

    Vector v1(   l2.y * (l3.z * l4.w - l3.w * l4.z) - l2.z * (l3.y * l4.w - l3.w * l4.y) + l2.w * (l3.y * l4.z - l3.z * l4.y),
              - (l1.y * (l3.z * l4.w - l3.w * l4.z) - l1.z * (l3.y * l4.w - l3.w * l4.y) + l1.w * (l3.y * l4.z - l3.z * l4.y)),
                 l1.y * (l2.z * l4.w - l2.w * l4.z) - l1.z * (l2.y * l4.w - l2.w * l4.y) + l1.w * (l2.y * l4.z - l2.z * l4.y),
              - (l1.y * (l2.z * l3.w - l2.w * l3.z) - l1.z * (l2.y * l3.w - l2.w * l3.y) + l1.w * (l2.y * l3.z - l2.z * l3.y)));
    Vector v2(- (l2.x * (l3.z * l4.w - l3.w * l4.z) - l2.z * (l3.x * l4.w - l3.w * l4.x) + l2.w * (l3.x * l4.z - l3.z * l4.x)),
                 l1.x * (l3.z * l4.w - l3.w * l4.z) - l1.z * (l3.x * l4.w - l3.w * l4.x) + l1.w * (l3.x * l4.z - l3.z * l4.x),
              - (l1.x * (l2.z * l4.w - l2.w * l4.z) - l1.z * (l2.x * l4.w - l2.w * l4.x) + l1.w * (l2.x * l4.z - l2.z * l4.x)),
                 l1.x * (l2.z * l3.w - l2.w * l3.z) - l1.z * (l2.x * l3.w - l2.w * l3.x) + l1.w * (l2.x * l3.z - l2.z * l3.x));
    Vector v3(   l2.x * (l3.y * l4.w - l3.w * l4.y) - l2.y * (l3.x * l4.w - l3.w * l4.x) + l2.w * (l3.x * l4.y - l3.y * l4.x),
              - (l1.x * (l3.y * l4.w - l3.w * l4.y) - l1.y * (l3.x * l4.w - l3.w * l4.x) + l1.w * (l3.x * l4.y - l3.y * l4.x)),
                 l1.x * (l2.y * l4.w - l2.w * l4.y) - l1.y * (l2.x * l4.w - l2.w * l4.x) + l1.w * (l2.x * l4.y - l2.y * l4.x),
              - (l1.x * (l2.y * l3.w - l2.w * l3.y) - l1.y * (l2.x * l3.w - l2.w * l3.x) + l1.w * (l2.x * l3.y - l2.y * l3.x)));
    Vector v4(- (l2.x * (l3.y * l4.z - l3.z * l4.y) - l2.y * (l3.x * l4.z - l3.z * l4.x) + l2.z * (l3.x * l4.y - l3.y * l4.x)),
                 l1.x * (l3.y * l4.z - l3.z * l4.y) - l1.y * (l3.x * l4.z - l3.z * l4.x) + l1.z * (l3.x * l4.y - l3.y * l4.x),
              - (l1.x * (l2.y * l4.z - l2.z * l4.y) - l1.y * (l2.x * l4.z - l2.z * l4.x) + l1.z * (l2.x * l4.y - l2.y * l4.x)),
                 l1.x * (l2.y * l3.z - l2.z * l3.y) - l1.y * (l2.x * l3.z - l2.z * l3.x) + l1.z * (l2.x * l3.y - l2.y * l3.x));

    Matrix4x4 adjoint(v1, v2, v3, v4);

    float invDet = 1.0f / det;
    Matrix4x4 inverseMatrix = adjoint * invDet;

    return inverseMatrix;
}

bool Matrix4x4::operator ==(Matrix4x4 m)
{
    return this->l1 == m.l1 && this->l2 == m.l2 && this->l3 == m.l3 && this->l4 == m.l4;
}

bool Matrix4x4::operator !=(Matrix4x4 m)
{
    return this->l1 != m.l1 || this->l2 != m.l2 || this->l3 != m.l3 || this->l4 != m.l4;
}

std::string Matrix4x4::to_string()
{
    std::stringstream ss;
    int s = 5;

    ss << "| " << std::setw(s) << l1.x << " " << std::setw(s) << l1.y << " " << std::setw(s) << l1.z << std::setw(s) << l1.w << " " << " |" << std::endl;
    ss << "| " << std::setw(s) << l2.x << " " << std::setw(s) << l2.y << " " << std::setw(s) << l2.z << std::setw(s) << l2.w << " " << " |" << std::endl;
    ss << "| " << std::setw(s) << l3.x << " " << std::setw(s) << l3.y << " " << std::setw(s) << l3.z << std::setw(s) << l3.w << " " << " |" << std::endl;
    ss << "| " << std::setw(s) << l4.x << " " << std::setw(s) << l4.y << " " << std::setw(s) << l4.z << std::setw(s) << l4.w << " " << " |" << std::endl;

    return ss.str();
}

Matrix4x4 Matrix4x4::zero() { return Matrix4x4(Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0)); }

/**
 * @brief Calculate the determinant of the 4x4 matrix
 * @return The determinant of the 4x4 matrix
 */
float Matrix4x4::determinant()
{
    return (l1.x * l2.y * l3.z * l4.w + l2.x * l3.y * l1.z * l4.w + l3.x * l1.y * l2.z * l4.w - l3.x * l2.y * l1.z * l4.
            w - l2.x * l1.y * l3.z * l4.w - l1.x * l3.y * l2.z * l4.w)
        - (l4.x * l1.y * l2.z * l3.w + l4.x * l2.y * l3.z * l1.w + l4.x * l3.y * l1.z * l2.w - l4.x * l3.y * l2.z * l1.w
            - l4.x * l2.y * l1.z * l3.w - l4.x * l1.y * l3.z * l2.w)
        + (l1.x * l4.y * l2.z * l3.w + l2.x * l4.y * l3.z * l1.w + l3.x * l4.y * l1.z * l2.w - l3.x * l4.y * l2.z * l1.w
            - l2.x * l4.y * l1.z * l3.w - l1.x * l4.y * l3.z * l2.w)
        - (l1.x * l2.y * l4.z * l3.w + l2.x * l3.y * l4.z * l1.w + l3.x * l1.y * l4.z * l2.w - l3.x * l2.y * l4.z * l1.w
            - l2.x * l1.y * l4.z * l3.w - l1.x * l3.y * l4.z * l2.w);
}

/**
 * @brief Calculate the transpose of the 4x4 matrix
 * @return The transpose of the 4x4 matrix
 */
Matrix4x4 Matrix4x4::transpose()
{
    return Matrix4x4(Vector(l1.x, l2.x, l3.x, l4.x), Vector(l1.y, l2.y, l3.y, l4.y), Vector(l1.z, l2.z, l3.z, l4.z),
                     Vector(l1.w, l2.w, l3.w, l4.w));
}
