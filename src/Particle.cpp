﻿#include "Particle.h"

Particle::Particle()
{
    this->position = Vector(0, 0, 0);
    this->velocity = Vector(0, 0, 0);
    this->acceleration = Vector(0, 0, 0);
    this->inversedMass = 0;
    this->time = 0;
}

Particle::Particle(Vector velocity, float mass)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->acceleration = Vector(0, -9.81, 0);
    this->inversedMass = 1 / mass;
    this->time = 0;
}

Particle::Particle(Vector velocity, float mass, float gravity)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->acceleration = Vector(0, -gravity, 0);
}

Particle::Particle(Vector velocity, float mass, float gravity, bool massInfluence)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->acceleration = massInfluence ? Vector(0, -gravity * mass, 0) : Vector(0, -gravity, 0);
}

Particle::Particle(Vector velocity, float mass, float gravity, int r, int g, int b)
{
    this->position = Vector(0, 0, 0);
    this->velocity = velocity;
    this->inversedMass = 1 / mass;
    this->time = 0;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

float Particle::getMass()
{
    return 1 / inversedMass;
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
 * @brief Calculate the new position of the particle using the Euler integration method
 * 
 * @param delta_t 
 */
void Particle::eulerIntegration(float delta_t)
{
    // Update the velocity of the particle...
    velocity.x += acceleration.x * delta_t;
    velocity.y += acceleration.y * delta_t;
    velocity.z += acceleration.z * delta_t;

    // ... and its position
    position.x += velocity.x * delta_t;
    position.y += velocity.y * delta_t;
    position.z += velocity.z * delta_t;
}
