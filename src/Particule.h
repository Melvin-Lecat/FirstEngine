#pragma once
#include "Vector.h"

class Particule
{
protected:
    float masse;

public:
    Vector position;
    Vector velocite;
    Vector acceleration;
    float temps;
    int color[3] = {255, 255, 255};


    Particule();
    Particule(Vector velocite, float masse);
    Particule(Vector velocite, float masse, float gravity);
    Particule(Vector velocite, float masse, float gravity, bool massInfluence);
    Particule(Vector velocite, float masse, float gravity, int r, int g, int b);

    void integration_euler(float deltat);

    float GetMasse(); // Getter et Setter de masse pour contourner les problèmes
    void SetMasse(float m);
    Particule* duplicate();
};
