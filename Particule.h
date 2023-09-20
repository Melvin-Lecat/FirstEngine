#pragma once
#include "ofMain.h"
#include "Vector.h"

class Particule {

public:
	Vector position;
	Vector velocite;
	Vector acceleration;
	float angle;
	float masse;
	float temps;


	Particule();
	Particule(Vector velocite, float angle, float masse);

	void integration_euler(float deltat);
};
