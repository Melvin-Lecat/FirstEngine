#pragma once

#include "ofMain.h"
#include "../Vector.h"
#include "../Particule.h"
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void UpdateParticle(Vector dir);
	void push(std::list<Particule*> tabParticule, float deltat);

	Vector pos = Vector(300, 300, 0);
	Vector velocite = Vector(50, 100, 0);

	std::list <Particule*> tabParticule;
	void AddParticule(std::list <Particule*> tabParticule, Particule* particule);

};
