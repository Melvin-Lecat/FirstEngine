#pragma once
#include "ofMain.h"
#include "Vector.h"

class Particule {

public:
	Vector position;
	Vector velocite;
	Vector acceleration;
	float vitesse_zero;
	float angle;
	float masse;
	float temps;


	Particule() {
		//
	}

	Particule(float vitesse, float angle, float masse) {
		this->position = Vector(0, 0, 0);
		this->velocite = Vector(0,0,0);
		this->acceleration = Vector(0, 0, 0);
		this->vitesse_zero = vitesse;
		this->angle = angle;
		this->masse = masse;
		this->temps = 0;
	}
};
