#include "Brick.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Brick::Brick() {
	o_shape = new RectangleShape(Vector2f(50.f, 20.f));
	o_width = 20.f;
	o_height = 50.f;
	o_shape->setOrigin(25.f, 25.f);
	o_shape->setFillColor(sf::Color::Green);
	o_life = 3;
}