#include "Quaternion.h"

Quaternion::Quaternion(float w, float x, float y, float z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion(float angle, Vector n)
{
    this->w = cos(angle / 2);
    this->x = sin(angle / 2) * n.x;
    this->y = sin(angle / 2) * n.y;
    this->z = sin(angle / 2) * n.z;
}

Quaternion Quaternion::operator /(float k)
{
    if (k != 0)
    {
        return Quaternion(this->w / k, this->x / k, this->y / k, this->z / k);
    }
}

Quaternion Quaternion::operator+(Quaternion q)
{
    return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
}

Quaternion Quaternion::toQuaternion(Vector v)
{
    return Quaternion(0, v.x, v.y, v.z);
}

std::string Quaternion::to_string()
{
    return "w: " + std::to_string(this->w) + "\n x: " + std::to_string(this->x) + "\n y: " + std::to_string(this->y) +
        "\n z: " + std::to_string(this->z);
}

glm::quat Quaternion::q()
{
    return glm::quat(w, x, y, z);
}

Quaternion Quaternion::negation(Quaternion q)
{
    return Quaternion(-q.w, -q.x, -q.y, -q.z);
}

Quaternion Quaternion::identitePos()
{
    return Quaternion(1, 0, 0, 0);
}

Quaternion Quaternion::identiteNeg()
{
    return Quaternion(-1, 0, 0, 0);
}

float Quaternion::norme(Quaternion q)
{
    return glm::sqrt(glm::pow2(q.w) + glm::pow2(q.x) + glm::pow2(q.y) + glm::pow2(q.z));
}

Quaternion Quaternion::conjugue(Quaternion q)
{
    return Quaternion(q.w, -q.x, -q.y, -q.z);
}

Quaternion Quaternion::inverse(Quaternion q)
{
    return conjugue(q) / norme(q);
}

Quaternion Quaternion::multiplication(Quaternion q1, Quaternion q2)
{
    return Quaternion(q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z),
                      q1.w * q2.x + q2.w * q1.x + (q1.y * q2.z - q1.z * q2.y),
                      q1.w * q2.y + q2.w * q1.y + (q1.z * q2.x - q1.x * q2.z),
                      q1.w * q2.z + q2.w * q1.z + (q1.x * q2.y - q1.y * q2.x));
}

Quaternion Quaternion::difference(Quaternion q1, Quaternion q2)
{
    return multiplication(q2, conjugue(q1));
}

float Quaternion::produitScalaire(Quaternion q1, Quaternion q2)
{
    return (q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
}

/*Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, float t)
{
    //return multiplication(multiplication(q2, inverse(q1)),q1);
    // Il manque la gestion de la puissance
}*/

Vector Quaternion::applyRotation(Vector v, Quaternion q)
{
    auto p = Quaternion(v.w, v.x, v.y, v.z);
    Quaternion final = multiplication(multiplication(q, p), conjugue(q));
    return Vector(final.x, final.y, final.z, final.w);
}

Matrix Quaternion::quatToMat()
{
    return Matrix(Vector(1 - 2 * (glm::pow2(this->y) + glm::pow2(this->z)), 2 * (this->x * this->y + this->z * this->w),
                         2 * (this->x * this->z - this->y * this->w)),
                  Vector(2 * (this->x * this->y - this->z * this->w), 1 - 2 * (glm::pow2(this->x) + glm::pow2(this->z)),
                         2 * (this->y * this->z + this->x * this->w)),
                  Vector(2 * (this->x * this->z + this->y * this->w), 2 * (this->y * this->z - this->x * this->w),
                         1 - 2 * (glm::pow2(this->x) + glm::pow2(this->y))));
}

Quaternion Quaternion::operator*(float val) { return Quaternion(w * val, x * val, y * val, z * val); }
