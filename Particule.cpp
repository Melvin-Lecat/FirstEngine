#include "Particule.h"

Particule::Particule()
{
    this->position = Vector(0, 0, 0);
    this->velocite = Vector(0, 0, 0);
    this->acceleration = Vector(0, 0, 0);
    this->angle = 0;
    this->masse = 0;
    this->temps = 0;
}

Particule::Particule(Vector velocite, float angle, float masse)
{
    this->position = Vector(0, 0, 0);
    this->velocite = velocite;
    this->acceleration = Vector(0, -9.81, 0);
    this->angle = angle;
    this->masse = masse;
    this->temps = 0;
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

