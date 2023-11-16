#include "ParticleRod.h"
#include "FixedSpringGenerator.h"

ParticleRod::ParticleRod(float k, float length, Particle* particle1, Particle* particle2)
{
    this->k = k;
    this->length = length;
    this->particle1 = particle1;
    this->particle2 = particle2;
}

void ParticleRod::updateForce(Particle* particle, float duration)
{
    FixedSpringGenerator fsg1(this->particle1->position, k, length);
    FixedSpringGenerator fsg2(this->particle2->position, k, length);

    Vector direction1 = (this->particle2->position - this->particle1->position).normalized();
    Vector velocityProj1 = this->particle1->velocity.projection(direction1);
    float stretch1 = length - this->particle2->position.distance(this->particle1->position);
    float force1 = k * stretch1;

    Vector direction2 = (this->particle1->position - this->particle2->position).normalized();
    Vector velocityProj2 = this->particle2->velocity.projection(direction2);
    float stretch2 = length - this->particle1->position.distance(this->particle2->position);
    float force2 = k * stretch2;
    cout << stretch1 << endl;
    float r = 5;
    if (glm::abs(stretch1) > r && glm::abs(stretch2) > r)
    {
        cout << "force" << endl;
        fsg1.updateForce(this->particle2, duration);
        fsg2.updateForce(this->particle1, duration);
    }
}
