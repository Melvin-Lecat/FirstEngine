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

Matrix4x4 Matrix4x4::zero() { return Matrix4x4(Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0)); }
