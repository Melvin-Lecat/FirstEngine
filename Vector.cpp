#include "Vector.h"

Vector Vector::operator +(Vector v) { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
Vector Vector::operator +=(Vector v) { return Vector(this->x + v.x, this->y + v.y, this->z + v.z); }
Vector Vector::operator - (Vector v) { return Vector(this->x - v.x, this->y - v.y, this->z - v.z); }
Vector Vector::operator * (Vector v) { return Vector(this->x * v.x, this->y * v.y, this->z * v.z); }
Vector Vector::operator * (float k) { return Vector(this->x * k, this->y * k, this->z * k); }

Vector Vector::Zero(){ return Vector(0, 0, 0); }
Vector Vector::OneX() { return Vector(1, 0, 0); }
Vector Vector::OneY() { return Vector(0, 1, 0); }
Vector Vector::OneZ() { return Vector(0, 0, 1); }

std::string Vector::to_string()
{
    return "x:" + std::to_string(this->x) + "\n y: " + std::to_string(this->y) + "\n z: " + std::to_string(this->z);
}

Vector Vector::Invert()
{
    return Vector(-x, -y, -z);
}

float Vector::Norme() { return glm::sqrt(glm::pow2(x) + glm::pow2(y) + glm::pow2(z)); }

float Vector::Norme2() { return glm::pow2(x) + glm::pow2(y) + glm::pow2(z); }

Vector Vector::Normalize() { return Vector(x, y, z) * (1 / Vector::Norme()); }

Vector Vector::Vectoriel(Vector v)
{
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}