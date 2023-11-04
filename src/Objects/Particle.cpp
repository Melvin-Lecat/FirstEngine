#include "Particle.h"

Particle::Particle()
{
    this->position = Vector(0, 0, 0);
    this->velocity = Vector(0, 0, 0);
    this->inversedMass = 0;
    this->time = 0;
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
    this->radius = 1;
    this->gravity = 9.81;
    this->shape = ofSpherePrimitive();
}

Particle::Particle(Vector velocity, float mass)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
    this->radius = 1;
    this->gravity = 9.81;
    this->shape = ofSpherePrimitive();
}

Particle::Particle(Vector velocity, float mass, float radius)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
    this->radius = radius;
    this->gravity = 9.81;
    this->shape = ofSpherePrimitive();
}

Particle::Particle(Vector velocity, float mass, float radius, float gravity)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
    this->radius = radius;
    this->gravity = gravity;
    this->shape = ofSpherePrimitive();
}

Particle::Particle(Vector velocity, float mass, int r, int g, int b, float radius)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->radius = radius;
    this->gravity = 9.81;
    this->shape = ofSpherePrimitive();
}


float Particle::getMass()
{
    return 1 / inversedMass;
}

float Particle::getInversedMass()
{
    return inversedMass;
}

void Particle::setMass(float m)
{
    inversedMass = 1 / m;
}

/**
 * @brief Duplicate the particle
 * 
 * @return Particule* 
 */
Particle* Particle::duplicate()
{
    return new Particle(*this);
}