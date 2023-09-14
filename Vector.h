#pragma once
#include <ofMain.h>

class Vector
{
public:
    glm::vec2 v2() { return glm::vec2(x, y); }
    glm::vec2 v3() { return glm::vec3(x, y, z); }

    float x, y, z, w;

    Vector()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }

    Vector(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->z = 0;
        this->w = 0;
    }

    Vector(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = 0;
    }

    Vector operator +(Vector v);
    Vector operator +=(Vector v);
    Vector operator -(Vector v);
    Vector operator *(Vector v); // Produit scalaire 
    Vector operator *(float k); // Multiplication par scalaire

    static Vector OneX(); // Methodes statiques pour g�n�rer des vecteurs unitaires
    static Vector OneY();
    static Vector OneZ();
    std::string to_string();

    Vector Invert(); // Negation 
    float Norme(); // Norme 1
    float Norme2(); // Norme 2
    Vector Normalize(); // Normalization du vecteur (verifier et optimiser peut etre)
    Vector Vectoriel(Vector v); // Produit vectoriel
};
