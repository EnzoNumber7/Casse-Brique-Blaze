#include "Border.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Border::Border() {
	o_shape = new RectangleShape(Vector2f(1.f, 1.f));
	o_shape->setOrigin(0.5f, 0.5f);
	o_life = NULL;
}