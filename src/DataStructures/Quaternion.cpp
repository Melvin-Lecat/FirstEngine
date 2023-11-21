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
    if (k == 0)
    {
        throw std::invalid_argument("Division by 0");
    }
    return Quaternion(this->w / k, this->x / k, this->y / k, this->z / k);
}

Quaternion Quaternion::operator*(float val) { return Quaternion(w * val, x * val, y * val, z * val); }

Quaternion Quaternion::operator*(Quaternion q)
{
    return Quaternion(this->w * q.w - (this->x * q.x + this->y * q.y + this->z * q.z),
                      this->w * q.x + q.w * this->x + (this->y * q.z - this->z * q.y),
                      this->w * q.y + q.w * this->y + (this->z * q.x - this->x * q.z),
                      this->w * q.z + q.w * this->z + (this->x * q.y - this->y * q.x));
}

Quaternion Quaternion::operator+(Quaternion q)
{
    return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
}

bool Quaternion::operator ==(Quaternion q)
{
    return (this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z);
}

bool Quaternion::operator !=(Quaternion q)
{
    return (this->w != q.w || this->x != q.x || this->y != q.y || this->z != q.z);
}

std::string Quaternion::to_string()
{
    return "w: " + std::to_string(this->w) + "\n x: " + std::to_string(this->x) + "\n y: " + std::to_string(this->y) +
        "\n z: " + std::to_string(this->z);
}

/**
 * @return the difference between the two quaternions
 */
Quaternion Quaternion::difference(Quaternion q)
{
    return q * conjugate(*this);
}

/**
 * @return the opposite quaternion
 */
Quaternion Quaternion::opposite(Quaternion q)
{
    return Quaternion(-q.w, -q.x, -q.y, -q.z);
}

/**
 * @return the quaternion corresponding to the vector
 */
Quaternion Quaternion::toQuaternion(Vector v)
{
    return Quaternion(0, v.x, v.y, v.z);
}

/**
 * @return the quaternion corresponding to the glm::quat
 */
glm::quat Quaternion::q()
{
    return glm::quat(w, x, y, z);
}

/**
 * @return the identity quaternion
 */
Quaternion Quaternion::identity()
{
    return Quaternion(1, 0, 0, 0);
}

/**
 * @return the magnitude of the quaternion
 */
float Quaternion::magnitude()
{
    return glm::sqrt(glm::pow2(w) + glm::pow2(x) + glm::pow2(y) + glm::pow2(z));
}

/**
 * @return the normalized quaternion
 */
Quaternion Quaternion::normalize()
{
    return *this / magnitude();
}

/**
 * @return the conjugate of the quaternion
 */
Quaternion Quaternion::conjugate(Quaternion q)
{
    return Quaternion(q.w, -q.x, -q.y, -q.z);
}

/**
 * @return the inverse of the quaternion
 */
Quaternion Quaternion::inverse()
{
    return conjugate(*this) / magnitude();
}

/**
 * @return the scalar product of the two quaternions
 */
float Quaternion::scalarProduct(Quaternion q)
{
    return (this->w * q.w + this->x * q.x + this->y * q.y + this->z * q.z);
}

/**
 * @return the vector after rotation
 */
Vector Quaternion::applyRotation(Vector v, Quaternion q)
{
    auto p = Quaternion(v.w, v.x, v.y, v.z);
    Quaternion final = (q * p) * conjugate(q);
    return Vector(final.x, final.y, final.z, final.w);
}

/**
 * @return the matrix corresponding to the quaternion
 */
Matrix Quaternion::quatToMat()
{
    return Matrix(Vector(1 - 2 * (glm::pow2(this->y) + glm::pow2(this->z)), 2 * (this->x * this->y + this->z * this->w),
                         2 * (this->x * this->z - this->y * this->w)),
                  Vector(2 * (this->x * this->y - this->z * this->w), 1 - 2 * (glm::pow2(this->x) + glm::pow2(this->z)),
                         2 * (this->y * this->z + this->x * this->w)),
                  Vector(2 * (this->x * this->z + this->y * this->w), 2 * (this->y * this->z - this->x * this->w),
                         1 - 2 * (glm::pow2(this->x) + glm::pow2(this->y))));
}
