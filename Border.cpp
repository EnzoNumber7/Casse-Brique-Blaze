#include "Border.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Border::Border(char position, GameWindow* window) {

	if (position == 'l' or position == 'r') {
		o_width = 50.f;
		o_height = window->w_height;
	}
	if (position == 'u' or position == 'd') {
		o_width = window->w_width;
		o_height = 50.f;

	}
	o_shape = new RectangleShape(Vector2f(o_width, o_height));
	o_shape->setOrigin(0.5f, 0.5f);
	o_life = NULL;
}