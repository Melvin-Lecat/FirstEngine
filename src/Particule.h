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
		float temps;
	
	
		
		Particule();
		Particule(Vector velocite, float masse);
		Particule(Vector velocite, float masse, float gravity);
		Particule(Vector velocite, float masse, float gravity, bool massInfluence);

		void integration_euler(float deltat);

	float GetMasse(); // Getter et Setter de masse pour contourner les problèmes
	void SetMasse(float m);
	Particule* duplicate();
};
