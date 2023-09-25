#include "ofApp.h"
#include <stdlib.h>
#define RAD 15

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetColor(255, 255, 255);
    cout << "User Manual:\n "
        "Press 'p' to pause simulation\n"
        "Press 'i' to clear all particles\n"
        "Press 'o' to add a particle\n"
        "Press the left arrow to update frame by frame while paused\n"
        "Click in the window to change the velocity\n" << endl;
}

void ofApp::CheckUnboundParticules()
{
    for (auto particule = tabParticule.begin(); particule != tabParticule.end();)  // Itères sur les particules entre le début et la fin de la liste
    {
       
        if ((*particule)->position.y < -RAD || (*particule)->position.x > static_cast<float>(ofGetWidth()) + RAD) // Vérifie si la particule est hors de l'écran (bas et droite)
        {
            delete *particule; // Libère la mémoire de la particule
            particule = tabParticule.erase(particule); // Supprime la particule de la liste
        }
        else
        {
            ++particule; // Donne l'élément suivant de la liste (itérateur: elem.suivant)
        }
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Checks all the particules and remove it if y <= 0
    CheckUnboundParticules();
    if (SimPause) return;
    UpdateParticles(tabParticule, ofGetLastFrameTime()); // ofGetLastFrameTime() is the time since the last frame
}

//--------------------------------------------------------------
void ofApp::draw()
{
    Vector cursor = Vector(velocite.x, ofGetHeight() - velocite.y);
    ofDrawLine(Vector(0, ofGetHeight()).v2(), cursor.v2());
    for (Particule* p : tabParticule)
    {
        Vector realPos = Vector(p->position.x, ofGetHeight() - p->position.y);
        ofDrawCircle(realPos.v2(), RAD);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case ' ':
        break;
    case 'p':
        SimPause = !SimPause;
        cout << "Pause? " << SimPause << endl;
        break;
    case 'i':
        ClearParticles();
        break;
    case 'o':
        tabParticule.push_back(new Particule(velocite, 45, 1));
        break;
    case OF_KEY_RIGHT: // Flèche droite
        if (SimPause) { UpdateParticles(tabParticule, ofGetLastFrameTime()); }
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    velocite = Vector(x, glm::abs(ofGetHeight() - y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}


void ofApp::UpdateParticles(std::list<Particule*> tabParticule, float deltat)
{
    //sert d'update
    // boucle de particule 
    for (Particule* p : tabParticule)
    {
        p->temps += deltat;

        //p->position.x = p->vitesse_zero * p->temps * cos(p->angle);
        //p->position.y = p->vitesse_zero * p->temps * sin(p->angle) + (0.5) * (-9.81) * glm::pow2(p->temps);

        //p->velocite.x = p->vitesse_zero * cos(p->angle);
        //p->velocite.y = p->vitesse_zero * sin(p->angle) + (-9.81) * p->temps;

        p->integration_euler(deltat);

        //cout << "Vitesse" << p->velocite.to_string() << "\n" << p->temps << endl;
    }
}

void ofApp::ClearParticles()
{
    cout << "Clear" << tabParticule.size() << endl;
    for (Particule* p : tabParticule)
    {
        delete p;
    }
    tabParticule.clear();
    cout << "Cleared" << tabParticule.size() << endl;
}

float ofApp::GetTimeElapsed()
{
    float currentTime = ofGetElapsedTimef();
    float lastFrameTime = ofGetLastFrameTime();
    return lastFrameTime / currentTime;
}
