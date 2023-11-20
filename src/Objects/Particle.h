#pragma once
#include "RigidBody.h"
#include "Drawable.h"
#include "Vector.h"

class Particle : public RigidBody, public Drawable
{
protected:
    float inversedMass;

public:
    float time;
    float radius;

    // Constructors
    Particle();
    Particle(Vector velocity, float mass);
    Particle(Vector velocity, float mass, float radius);
    Particle(Vector velocity, float mass, float radius, float gravity);
    Particle(Vector velocity, float mass, int r, int g, int b, float radius);

    // Methods
    float getMass();
    float getInversedMass();
    void setMass(float m);
    Particle* duplicate();
    bool checkCollision(Particle* particle);
    void draw() override;
    void updateColor() ;
};
