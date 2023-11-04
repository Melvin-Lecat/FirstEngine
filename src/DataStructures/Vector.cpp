#include "Vector.h"

#include <string>

Vector::Vector()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
    this->w = 0;
}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
}


Vector Vector::operator +(Vector v) { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
Vector Vector::operator +=(Vector v) { return Vector(this->x += v.x, this->y += v.y, this->z += v.z); }
Vector Vector::operator -(Vector v) { return Vector(this->x - v.x, this->y - v.y, this->z - v.z); }
Vector Vector::operator -=(Vector v) { return Vector(this->x -= v.x, this->y -= v.y, this->z -= v.z); }

bool Vector::operator ==(Vector v) { return this->x == v.x && this->y == v.y && this->z == v.z; }

float Vector::operator *(Vector v) { return this->x * v.x + this->y * v.y; }
float Vector::operator *=(Vector v) { return this->x * v.x + this->y * v.y; }
Vector Vector::operator *(float k) { return Vector(this->x * k, this->y * k, this->z * k); }
Vector Vector::operator *=(float k) { return Vector(this->x *= k, this->y *= k, this->z *= k); }

std::string Vector::to_string()
{
    return "x:" + std::to_string(this->x) + "\n y: " + std::to_string(this->y) + "\n z: " + std::to_string(this->z);
}

Vector Vector::zero() { return Vector(0, 0, 0); }
Vector Vector::oneX() { return Vector(1, 0, 0); }
Vector Vector::oneY() { return Vector(0, 1, 0); }
Vector Vector::oneZ() { return Vector(0, 0, 1); }

/**
 * @return the opposite vector
 */
Vector Vector::opposite()
{
    return Vector(-x, -y, -z);
}

/**
 * @return the magnitude of the vector
 */
float Vector::magnitude() { return glm::sqrt(glm::pow2(x) + glm::pow2(y) + glm::pow2(z)); }

/**
 * @return the squared magnitude of the vector
 */
float Vector::squaredMagnitude() { return glm::pow2(x) + glm::pow2(y) + glm::pow2(z); }

/**
 * @param other the other vector
 * @return the distance between the two vectors
 */
float Vector::distance(Vector other)
{
    return glm::sqrt(glm::pow2(x - other.x) + glm::pow2(y - other.y) + glm::pow2(z - other.z));
}

/**
 * @return the normalized vector
 */
Vector Vector::normalized() { return magnitude() == 0 ? Vector(0, 0, 0) : Vector(x, y, z) * (1 / magnitude()); }

/**
 * @param w the other vector
 * @return the vectorial product of the two vectors
 */
Vector Vector::vectorialProduct(Vector w)
{
    return Vector(y * w.z - z * w.y, z * w.x - x * w.z, x * w.y - y * w.x);
}
