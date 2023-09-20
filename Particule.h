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


	Particule();
	Particule(float vitesse, float angle, float masse);

	void integration_euler(float deltat);
};
