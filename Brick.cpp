#include "Brick.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Brick::Brick(int hp) {
	o_shape = new RectangleShape(Vector2f(50.f, 20.f));
	o_width = 50.f;
	o_height = 20.f;
	o_shape->setOrigin(25.f, 10.f);
	o_life = hp;
	switch (o_life) {
	case (1):
		o_shape->setFillColor(sf::Color::Red);
		break;
	case (2):
		o_shape->setFillColor(sf::Color::Yellow);
		break;
	case (3):
		o_shape->setFillColor(sf::Color::Green);
		break;
	case (4):
		o_shape->setFillColor(sf::Color::Blue);
		break;
	case (5):
		o_shape->setFillColor(sf::Color::Magenta);
		break;
	case (6):
		o_shape->setFillColor(sf::Color::White);
		break;
	}
}