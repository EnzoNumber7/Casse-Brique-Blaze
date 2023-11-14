#include "math.h"
#include <cmath>
#include <iostream>


void math::Normalize(float* VectX, float* VectY) {
	*VectX = *VectX / (float)sqrt(pow(*VectX, 2) + pow(*VectY, 2));
	*VectY = *VectY / (float)sqrt(pow(*VectX, 2) + pow(*VectY, 2));
}

sf::Vector2f math::RotateVect(float X, float Y, float angle) {
	double rad = (3.1415926535 / 180) * angle;
	//std::cout <<X * cos(rad) + Y * sin(rad) << std::endl;
	sf::Vector2f Vect;
	Vect.x = X * cos(rad) - Y * sin(rad);
	Vect.y = X * sin(rad) + Y * cos(rad);

	Normalize(&Vect.x, &Vect.y);
	return Vect;
}