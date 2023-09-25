#include "Matrice.h"

Matrice Matrice::operator +(Matrice v) { return Matrice(this->a + v.a, this->b + v.b, this->c + v.c, this->d + v.d, this->e + v.e, this->f + v.f, this->g + v.g, this->h + v.h, this->i + v.i); }
Matrice Matrice::operator +=(Matrice v) { return Matrice(this->a + v.a, this->b + v.b, this->c + v.c, this->d + v.d, this->e + v.e, this->f + v.f, this->g + v.g, this->h + v.h, this->i + v.i); }
Matrice Matrice::operator - (Matrice v) { return Matrice(this->a - v.a, this->b - v.b, this->c - v.c, this->d - v.d, this->e - v.e, this->f - v.f, this->g - v.g, this->h - v.h, this->i - v.i); }
Matrice Matrice::operator -= (Matrice v) { return Matrice(this->a - v.a, this->b - v.b, this->c - v.c, this->d - v.d, this->e - v.e, this->f - v.f, this->g - v.g, this->h - v.h, this->i - v.i); }
Matrice Matrice::operator * (Matrice v) { return Matrice((this->a * v.a) + (this->b * v.d) + (this->c * v.g),     (this->a * v.b) + (this->b * v.e) + (this->c * v.h),     (this->a * v.c) + (this->b * v.f) + (this->c * v.i),    (this->d * v.a) + (this->e * v.d) + (this->f * v.g),     (this->d * v.b) + (this->e * v.e) + (this->f * v.h),     (this->d * v.c) + (this->e * v.f) + (this->f * v.i),    (this->g * v.a) + (this->h * v.d) + (this->i * v.g),     (this->g * v.b) + (this->h * v.e) + (this->i * v.h),     (this->g * v.c) + (this->h * v.f) + (this->i * v.i)); }
Matrice Matrice::operator *= (Matrice v) { return Matrice((this->a * v.a) + (this->b * v.d) + (this->c * v.g),     (this->a * v.b) + (this->b * v.e) + (this->c * v.h),     (this->a * v.c) + (this->b * v.f) + (this->c * v.i),    (this->d * v.a) + (this->e * v.d) + (this->f * v.g),     (this->d * v.b) + (this->e * v.e) + (this->f * v.h),     (this->d * v.c) + (this->e * v.f) + (this->f * v.i),    (this->g * v.a) + (this->h * v.d) + (this->i * v.g),     (this->g * v.b) + (this->h * v.e) + (this->i * v.h),     (this->g * v.c) + (this->h * v.f) + (this->i * v.i)); }
Matrice Matrice::operator * (float k) { return Matrice(this->a * k, this->b * k, this->c * k, this->d * k, this->e * k, this->f * k, this->g * k, this->h * k, this->i * k); }
Matrice Matrice::operator *= (float k) { return Matrice(this->a * k, this->b * k, this->c * k, this->d * k, this->e * k, this->f * k, this->g * k, this->h * k, this->i * k); }

Matrice Matrice::Zero(){ return Matrice(0, 0, 0, 0, 0, 0, 0, 0, 0); }

std::string Matrice::to_string()
{
    return "a:" + std::to_string(this->a) + "   b: " + std::to_string(this->b) + "   c: " + std::to_string(this->c) + "\n " + "d:" + std::to_string(this->d) + "   e: " + std::to_string(this->e) + "   f: " + std::to_string(this->f) + "\n " + "g:" + std::to_string(this->g) + "   h: " + std::to_string(this->h) + "   i: " + std::to_string(this->i);
}
