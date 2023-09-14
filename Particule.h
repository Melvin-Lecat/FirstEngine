#pragma once
#include "ofMain.h"
#include "Vector.h"

class Particule {

public:
	Vector position;
	Vector velocite;
	Vector acceleration;
	float vitesse;
	float angle;
	float masse;
	float temps;


	Particule() {
		//
	}

	Particule(float vitesse, float angle, float masse) {
		this->position = (0,0,0);
		this->velocite = (0,0,0);
		this->acceleration = (0, 0, 0);
		this->vitesse = vitesse;
		this->angle = angle;
		this->masse = masse;
		this->temps = 0;
	}

	void push(Particule tabParticule[], float deltat) { //sert d'update
		// boucle de particule 
		for (i = 0; i <= tabParticule.size(); i = i + 1) {
			tabParticule[i].temps += 1;

			tabParticule[i].position.x = tabParticule[i].vitesse * tabParticule[i].temps * cos(tabParticule[i].angle);
			tabParticule[i].position.y = tabParticule[i].vitesse * tabParticule[i].temps * sin(tabParticule[i].angle) + (1 / 2) * (-9.81) * tabParticule[i].temps;

			tabParticule[i].velocite.x = tabParticule[i].vitesse * cos(tabParticule[i].angle);
			tabParticule[i].velocite.y = tabParticule[i].vitesse * sin(tabParticule[i].angle) + (-9.81) * tabParticule[i].temps;
		}
	}
}
