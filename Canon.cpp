#include "Canon.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Canon::Canon() {
	o_shape = new RectangleShape(Vector2f(50.f, 100.f));
	o_shape->setOrigin(25.f, 0.f);
	o_width = 50.f;
	o_height = 100.f;
}
