#include "Particle.h"

Particle::Particle()
{
    this->position = Vector(0, 0, 0);
    this->linearVelocity = Vector(0, 0, 0);
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
    this->linearVelocity = velocity;
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
    this->linearVelocity = velocity;
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
    this->linearVelocity = velocity;
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
    this->linearVelocity = velocity;
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


/**
 * @brief Check the collision with another particle
 *
 * @return bool
 */
bool Particle::checkCollision(Particle* particle)
{
    float d = (position - particle->position).squaredMagnitude();
    float minD = glm::pow2(radius + particle->radius);
    return (d <= minD);
}

/**
 * @brief Draw the particle
 *
 */
void Particle::draw()
{
    ofSetColor(color[0], color[1], color[2]);
    auto realPos = Vector(position.x, ofGetHeight() - position.y);
    ofDrawCircle(realPos.v2(), radius);
    ofSetColor(255, 255, 255);
}

/**
 * @brief Update the color of the Particle with the velocity
 *
 */
void Particle::updateColor()
{
    float xPos = position.x; // Obtenez la coordonnée X de la particule
    float yPos = position.y; // Obtenez la coordonnée Y de la particule

    // Calcul de la distance de la particule à la diagonale
    float distanceToDiagonal = yPos / ofGetHeight() - xPos / ofGetWidth();
    float absDistance = abs(distanceToDiagonal);

    // Déclaration et définition des couleurs
    int color1[3] = {0, 139, 139}; // Jaune (Rouge, Vert, Bleu)
    int color2[3] = {102, 51, 153}; // Cyan (Rouge, Vert, Bleu)
    int color3[3] = {0, 255, 127}; // Magenta (Rouge, Vert, Bleu)

    if (distanceToDiagonal < 0)
    {
        color[0] = (color2[0] + (color1[0] - color2[0]) * absDistance); // Rouge
        color[1] = (color2[1] + (color1[1] - color2[1]) * absDistance); // Vert
        color[2] = (color2[2] + (color1[2] - color2[2]) * absDistance); // Bleu
    }
    else
    {
        color[0] = (color2[0] + (color3[0] - color2[0]) * absDistance); // Rouge
        color[1] = (color2[1] + (color3[1] - color2[1]) * absDistance); // Vert
        color[2] = (color2[2] + (color3[2] - color2[2]) * absDistance); // Bleu
    }
}
