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

/**
 * @brief Add a force to the particle
 * 
 * @param force 
 */
void Particle::addForce(Vector force)
{
    this->accumForce += force;
}

/**
 * @brief Clear the forces associated to the particle
 * 
 */
void Particle::clearAccum()
{
    this->accumForce = Vector(0, 0, 0);
}

/**
 * @brief Calculate the new position of the particle using the Euler integration method
 * 
 * @param delta_t 
 */
void Particle::eulerIntegration(float delta_t)
{
    // Update the velocity of the particle...
    velocity += accumForce * delta_t * pow(0.2, delta_t);

    // ... and its position
    position += velocity * delta_t;
    clearAccum();
}
