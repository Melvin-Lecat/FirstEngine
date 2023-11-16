
/**
 * @brief Update the particles with the Euler method
 * 
 * @param tabParticle the list of particles to update
 * @param deltaT the delta time
 */


#include <iostream>
#include <list>

#include "../Objects/Particle.h"


std::list<Particle*> tabParticle;
void updateParticles(std::list<Particle*> tabParticle, float deltaT)
{
    // Iterates over the list of particles
    for (Particle* p : tabParticle)
    {
        // Update the time
        p->time += deltaT;
        // Update the position
        p->eulerIntegration(deltaT);
    }
}

/**
 * @brief Remove all the particles from the list and release the memory
 * 
 */
void clearParticles()
{
    std::cout << "Clear" << tabParticle.size() << endl;
    for (Particle* p : tabParticle)
    {
        delete p;
    }
    tabParticle.clear();
    cout << "Cleared" << tabParticle.size() << endl;
}
