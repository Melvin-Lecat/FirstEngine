#include "ofApp.h"
#include <stdlib.h>
#define RAD 15

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (SimPause) return;
	
	push(tabParticule, 0.1f);
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	Vector cursor = Vector(velocityDir.x, ofGetHeight() - velocityDir.y);
	ofDrawLine(Vector(0,ofGetHeight()).v2(), cursor.v2());
	for (Particule* p : tabParticule) {
		Vector realPos = Vector(p->position.x,ofGetHeight()-p->position.y);
		ofDrawCircle(realPos.v2(), RAD);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
		case ' ':
			break;
		case 'p':
			SimPause = !SimPause;
			cout <<"Pause? " << SimPause << endl;
			break;
		case 'i':
			ClearParticles();
			break;
		case 'o':
			tabParticule.push_back(new Particule(100,45,1));
			break;
	case OF_KEY_RIGHT:
		if(SimPause){push(tabParticule, 0.1f);}
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
	velocityDir = Vector(x,glm::abs(ofGetHeight()-y));
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


void ofApp::push(std::list<Particule*> tabParticule, float deltat) { //sert d'update
	// boucle de particule 
	for (Particule* p : tabParticule) {
		p->temps += deltat;

		p->position.x = p->vitesse_zero * p->temps * cos(p->angle);
		p->position.y = p->vitesse_zero * p->temps * sin(p->angle) + (0.5) * (-9.81) * glm::pow2(p->temps);

		p->velocite.x = p->vitesse_zero * cos(p->angle);
		p->velocite.y = p->vitesse_zero * sin(p->angle) + (-9.81) * p->temps;
		//cout << "Vitesse" << p->velocite.to_string() << "\n" << p->temps << endl;

	}
}

void ofApp::ClearParticles()
{
	cout << "Clear" << tabParticule.size() << endl;
	for (Particule* p : tabParticule) {
		delete p;
	}
	tabParticule.clear();
	cout << "Cleared" << tabParticule.size() << endl;
}
