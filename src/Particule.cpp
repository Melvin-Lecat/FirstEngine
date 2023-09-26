#include "Particule.h"

float Particule::GetMasse()
{
    return 1/masse;
}

void Particule::SetMasse(float m)
{
    masse = 1/m;
}

Particule* Particule::duplicate()
{
    return new Particule(*this);
}

Particule::Particule()
{
    this->position = Vector(0, 0, 0);
    this->velocite = Vector(0, 0, 0);
    this->acceleration = Vector(0, 0, 0);
    this->masse = 0;
    this->temps = 0;
}

Particule::Particule(Vector velocite, float masse)
{
    this->position = Vector(0, 0, 0);
    this->velocite = velocite;
    this->acceleration = Vector(0, -9.81, 0);
    this->masse = 1/masse;
    this->temps = 0;
}

Particule::Particule(Vector velocite, float masse, float gravity)
{
    this->position = Vector(0, 0, 0);
    this->velocite = velocite;
    this->masse = 1/masse;
    this->temps = 0;
    this->acceleration = Vector(0, -gravity, 0);
}

Particule::Particule(Vector velocite, float masse, float gravity, bool massInfluence)
{
    this->position = Vector(0, 0, 0);
    this->velocite = velocite;
    this->masse = 1/masse;
    this->temps = 0;
    this->acceleration = massInfluence? Vector(0, -gravity*masse, 0): Vector(0, -gravity, 0);
}
Particule::Particule(Vector velocite, float masse, float gravity, int r, int g, int b)
{
    this->position = Vector(0, 0, 0);
    this->velocite = velocite;
    this->masse = 1/masse;
    this->temps = 0;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

void Particule::integration_euler(float deltat)
{
    velocite.x += acceleration.x * deltat;
    velocite.y += acceleration.y * deltat;
    velocite.z += acceleration.z * deltat;
    
    position.x += velocite.x * deltat;
    position.y += velocite.y * deltat;
    position.z += velocite.z * deltat;
}

