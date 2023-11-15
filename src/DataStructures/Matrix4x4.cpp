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
    return Matrix4x4(this->l1 + m.l1, this->l2 + m.l2, this->l3 + m.l3);
}

Matrix4x4 Matrix4x4::operator +=(Matrix4x4 m)
{
    return Matrix4x4(this->l1 + m.l1, this->l2 + m.l2, this->l3 + m.l3);
}

Matrix4x4 Matrix4x4::operator -(Matrix4x4 m)
{
    return Matrix4x4(this->l1 - m.l1, this->l2 - m.l2, this->l3 - m.l3);
}

Matrix4x4 Matrix4x4::operator -=(Matrix4x4 m)
{
    return Matrix4x4(this->l1 - m.l1, this->l2 - m.l2, this->l3 - m.l3);
}

Matrix4x4 Matrix4x4::operator *(Matrix4x4 m)
{
    return Matrix4x4(Vector((this->l1.x * m.l1.x) + (this->l1.y * m.l2.x) + (this->l1.z * m.l3.x),
                            (this->l1.x * m.l1.y) + (this->l1.y * m.l2.y) + (this->l1.z * m.l3.y),
                            (this->l1.x * m.l1.z) + (this->l1.y * m.l2.z) + (this->l1.z * m.l3.z)),
                     Vector((this->l2.x * m.l1.x) + (this->l2.y * m.l2.x) + (this->l2.z * m.l3.x),
                            (this->l2.x * m.l1.y) + (this->l2.y * m.l2.y) + (this->l2.z * m.l3.y),
                            (this->l2.x * m.l1.z) + (this->l2.y * m.l2.z) + (this->l2.z * m.l3.z)),
                     Vector((this->l3.x * m.l1.x) + (this->l3.y * m.l2.x) + (this->l3.z * m.l3.x),
                            (this->l3.x * m.l1.y) + (this->l3.y * m.l2.y) + (this->l3.z * m.l3.y),
                            (this->l3.x * m.l1.z) + (this->l3.y * m.l2.z) + (this->l3.z * m.l3.z)));
}

Matrix4x4 Matrix4x4::operator *=(Matrix4x4 m)
{
    return Matrix4x4(Vector((this->l1.x * m.l1.x) + (this->l1.y * m.l2.x) + (this->l1.z * m.l3.x),
                            (this->l1.x * m.l1.y) + (this->l1.y * m.l2.y) + (this->l1.z * m.l3.y),
                            (this->l1.x * m.l1.z) + (this->l1.y * m.l2.z) + (this->l1.z * m.l3.z)),
                     Vector((this->l2.x * m.l1.x) + (this->l2.y * m.l2.x) + (this->l2.z * m.l3.x),
                            (this->l2.x * m.l1.y) + (this->l2.y * m.l2.y) + (this->l2.z * m.l3.y),
                            (this->l2.x * m.l1.z) + (this->l2.y * m.l2.z) + (this->l2.z * m.l3.z)),
                     Vector((this->l3.x * m.l1.x) + (this->l3.y * m.l2.x) + (this->l3.z * m.l3.x),
                            (this->l3.x * m.l1.y) + (this->l3.y * m.l2.y) + (this->l3.z * m.l3.y),
                            (this->l3.x * m.l1.z) + (this->l3.y * m.l2.z) + (this->l3.z * m.l3.z)));
}

Matrix4x4 Matrix4x4::operator *(float k)
{
    return Matrix4x4(this->l1 * k, this->l2 * k, this->l3 * k);
}

Matrix4x4 Matrix4x4::operator *=(float k)
{
    return Matrix4x4(this->l1 * k, this->l2 * k, this->l3 * k);
}

Matrix4x4 Matrix4x4::zero() { return Matrix4x4(Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0)); }
