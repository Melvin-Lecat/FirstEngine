#include "CollisionManager2D.h"

#include "Particle.h"
#include "DataStructures/Vector.h"

/**
 * @brief Return the new velocity of the Particle 1 when in collision with the Particle 2
 *
 */
Vector CollisionManager2D::ApplyCollision(float e, Particle* p1, Particle p2)
{
    Vector n = (p2.position - p1->position).normalized();
    float K = n * (p1->velocity - p2.velocity) * (e + 1) / (p1->getInversedMass() + p2.getInversedMass());
    //auto P = p1.velocity * p1.getMass();
    auto updatedVelocity = p1->velocity - n * K * p1->getInversedMass();
    auto move = updatedVelocity.normalized() * glm::abs((p1->radius + p2.radius) - p1->position.distance(p2.position));
    p1->position += move * (p1->getMass() / (p1->getMass() + p2.getMass()));
    return updatedVelocity;
}

/**
 * @brief Check all the collisions between each particle
 *
 */
void CollisionManager2D::CheckCollision(std::list<Particle*> tabParticle)
{
    int numCollisions = 0;
    int tests = 0;
    // Iterates over the list of particles
    for (auto particle1 = tabParticle.begin(); particle1 != tabParticle.end();)
    {
        // Iterates over the list of particles not yet checked
        for (auto particle2 = tabParticle.begin(); particle2 != particle1;)
        {
            // Gets the distance and the minimal distance between the particles (squared values to be faster)
            float d = ((*particle1)->position - (*particle2)->position).squaredMagnitude();
            float minD = glm::pow2((*particle1)->radius + (*particle2)->radius);

            // Collision only if the distance is lower than the minimal distance

            if (d <= minD)
            {
                float e = 0.9f;
                ++numCollisions;
                Particle* p1 = (*particle1);
                Particle* p2 = (*particle2);
                // P' = P + Kn
                // Applica1tion de la force sur P1
                Particle* p1Copy = p1->duplicate();

                p1->velocity = ApplyCollision(e, p1, *p2);

                // Application de la force sur P2
                p2->velocity = ApplyCollision(e, p2, *p1Copy);
            }
            ++tests;

            ++particle2;
        }
        ++particle1;
    }
    if (numCollisions)
        cout << "Number of collisions: " << numCollisions << "\r" << flush;
}
