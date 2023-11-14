#pragma once

#include <SFML/Graphics.hpp>

namespace math {
	void Normalize(float* VectX,float* VectY);
	sf::Vector2f RotateVect(float VectX, float VectY, float angle);
}
