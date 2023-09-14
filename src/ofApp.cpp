#include "ofApp.h"
#include <stdlib.h>
#define RAD 30

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetColor(255, 255, 255);
	tabParticule.push_back(new Particule(5, 45, 1));
}

//--------------------------------------------------------------
void ofApp::update() {
	push(tabParticule, 1);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofDrawCircle(this->pos.v2(), RAD);
	for (Particule* p : tabParticule) {
		ofDrawCircle(p->position.v2(), RAD);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case 'z':
		ofApp::UpdateParticle(Vector::OneY().Invert());
		break;
	case 's':
		ofApp::UpdateParticle(Vector::OneY());
		break;
	case 'q':
		ofApp::UpdateParticle(Vector::OneX().Invert());
		break;
	case 'd':
		ofApp::UpdateParticle(Vector::OneX());
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::UpdateParticle(Vector dir) {
	std::cout << "Update" << std::endl;
	this->pos = this->pos + dir * 10;
}

void ofApp::push(std::list<Particule*> tabParticule, float deltat) { //sert d'update
	// boucle de particule 
	for (Particule* p : tabParticule) {
		p->temps += deltat;

		p->position.x = p->vitesse_zero * p->temps * cos(p->angle);
		p->position.y = p->vitesse_zero * p->temps * sin(p->angle) + (1 / 2) * (-9.81) * p->temps;

		p->velocite.x = p->vitesse_zero * cos(p->angle);
		p->velocite.y = p->vitesse_zero * sin(p->angle) + (9.81) * p->temps;
		cout << "Vitesse" << p->velocite.to_string() << "\n" << p->temps << endl;
	}
}