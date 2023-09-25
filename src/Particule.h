#pragma once
#include "ofMain.h"
#include "Vector.h"

class Particule {

	protected:
		float masse;
	public:
		Vector position;
		Vector velocite;
		Vector acceleration;
		float angle;
		float temps;
	
	
		
		Particule();
		Particule(Vector velocite, float angle, float masse);
		
		void integration_euler(float deltat);

	float GetMasse(); // Getter et Setter de masse pour contourner les problèmes
	void SetMasse(float m);
};
