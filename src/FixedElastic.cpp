﻿#include "FixedElastic.h"

FixedElastic::FixedElastic(Vector point, float K, float length)
{
    this->point = point;
    this->K = K;
    this->length = length;
}

void FixedElastic::updateForce(Particle* particle, float duration)
{
    if (particle->position.distance(point) > length)
    {
        // Direction * K * longueur du ressort
        particle->addForce(
            (this->point - particle->position).normalized() * K * glm::abs(
                length - particle->position.distance(point)));
    }
}
