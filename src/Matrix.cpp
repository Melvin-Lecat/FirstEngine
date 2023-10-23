#include "Matrix.h"

Matrix Matrix::operator +(Matrix m)
{
    return Matrix(this->a + m.a, this->b + m.b, this->c + m.c, this->d + m.d, this->e + m.e, this->f + m.f,
                   this->g + m.g, this->h + m.h, this->i + m.i);
}

Matrix Matrix::operator +=(Matrix m)
{
    return Matrix(this->a += m.a, this->b += m.b, this->c += m.c, this->d += m.d, this->e += m.e, this->f += m.f,
                   this->g += m.g, this->h += m.h, this->i += m.i);
}

Matrix Matrix::operator -(Matrix m)
{
    return Matrix(this->a - m.a, this->b - m.b, this->c - m.c, this->d - m.d, this->e - m.e, this->f - m.f,
                   this->g - m.g, this->h - m.h, this->i - m.i);
}

Matrix Matrix::operator -=(Matrix m)
{
    return Matrix(this->a -= m.a, this->b -= m.b, this->c -= m.c, this->d -= m.d, this->e -= m.e, this->f -= m.f,
                   this->g -= m.g, this->h -= m.h, this->i -= m.i);
}

Matrix Matrix::operator *(Matrix m)
{
    return Matrix((this->a * m.a) + (this->b * m.d) + (this->c * m.g),
                   (this->a * m.b) + (this->b * m.e) + (this->c * m.h),
                   (this->a * m.c) + (this->b * m.f) + (this->c * m.i),
                   (this->d * m.a) + (this->e * m.d) + (this->f * m.g),
                   (this->d * m.b) + (this->e * m.e) + (this->f * m.h),
                   (this->d * m.c) + (this->e * m.f) + (this->f * m.i),
                   (this->g * m.a) + (this->h * m.d) + (this->i * m.g),
                   (this->g * m.b) + (this->h * m.e) + (this->i * m.h),
                   (this->g * m.c) + (this->h * m.f) + (this->i * m.i));
}

Matrix Matrix::operator *=(Matrix m)
{
    return Matrix((this->a *= m.a) + (this->b *= m.d) + (this->c *= m.g),
                   (this->a *= m.b) + (this->b *= m.e) + (this->c *= m.h),
                   (this->a *= m.c) + (this->b *= m.f) + (this->c *= m.i),
                   (this->d *= m.a) + (this->e *= m.d) + (this->f *= m.g),
                   (this->d *= m.b) + (this->e *= m.e) + (this->f *= m.h),
                   (this->d *= m.c) + (this->e *= m.f) + (this->f *= m.i),
                   (this->g *= m.a) + (this->h *= m.d) + (this->i *= m.g),
                   (this->g *= m.b) + (this->h *= m.e) + (this->i *= m.h),
                   (this->g *= m.c) + (this->h *= m.f) + (this->i *= m.i));
}

Matrix Matrix::operator *(float k)
{
    return Matrix(this->a * k, this->b * k, this->c * k, this->d * k, this->e * k, this->f * k, this->g * k,
                   this->h * k, this->i * k);
}

Matrix Matrix::operator *=(float k)
{
    return Matrix(this->a *= k, this->b *= k, this->c *= k, this->d *= k, this->e *= k, this->f *= k, this->g *= k,
                   this->h *= k, this->i *= k);
}

std::string Matrix::to_string()
{
    return "a:" + std::to_string(this->a) + "   b: " + std::to_string(this->b) + "   c: " + std::to_string(this->c) +
        "\n " + "d:" + std::to_string(this->d) + "   e: " + std::to_string(this->e) + "   f: " + std::to_string(this->f)
        + "\n " + "g:" + std::to_string(this->g) + "   h: " + std::to_string(this->h) + "   i: " +
        std::to_string(this->i);
}

/**
 * @return an empty matrix
 */
Matrix Matrix::zero() { return Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0); }