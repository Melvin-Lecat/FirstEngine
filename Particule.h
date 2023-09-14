#pragma once
#include "ofMain.h"
#include "Vector.h"

class Particule {

private:
    Vector position;
    Vector velocite;
    Vector acceleration;
    float masse;

public:
    Particule() {
        //
    }

    Particule(Vector position, Vector velocite, Vector acceleration, float masse) {
        this->position = position;
        this->velocite = velocite;
        this->acceleration = acceleration;
        this->masse = 1/masse;
    }

    void push(Particule p1) { //sert d'update
        //vitesse initiale
        float vitinit;

        //angle de la trajectoire
        float angle;

        velocite.v3().x = vitinit * cos(angle);
        velocite.v3().y = vitinit * sin(angle);
        velocite.v3().z = 0;

        position.v3().x = vitinit * cos(angle); // * t (en fonction des frames)
        position.v3().x = 1/2*t*g	vitinit * sin(angle); // * t (en fonction des frames)
        position.v3().z = 0; // * t (en fonction des frames)



    }
}