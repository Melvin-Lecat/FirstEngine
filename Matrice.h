#pragma once
#include <ofMain.h>

class Matrice
{
public:
	glm::mat3x3 m9() { return glm::mat3x3(a, b, c, d, e, f, g, h, i); }
	
    float a, b, c, d, e, f, g , h, i, j , k, l;

	Matrice()
    {
    	this->a = 0;
    	this->b = 0;
    	this->c = 0;
    	this->d = 0;
    	this->e = 0;
    	this->f = 0;
    	this->g = 0;
    	this->h = 0;
    	this->i = 0;
    	this->j = 0;
    	this->k = 0;
    	this->l = 1;
    }
	
    Matrice(float a, float b, float c, float d, float e, float f, float g, float h, float i)
    {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
		this->g = g;
		this->h = h;
		this->i = i;
		this->j = 0;
		this->k = 0;
		this->l = 1;
    }
	

	Matrice operator +(Matrice v);
	Matrice operator +=(Matrice v);
	Matrice operator -(Matrice v);
	Matrice operator -=(Matrice v);
	Matrice operator *(Matrice v); // Produit scalaire 
	Matrice operator *=(Matrice v); // Produit scalaire 
	Matrice operator *(float k);  // Multiplication par scalaire
	Matrice operator *=(float k);  // Multiplication par scalaire

	static Matrice Zero();
	
	std::string to_string();


};
