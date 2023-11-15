#include <SFML/Graphics.hpp>

#include "Border.h"

#include "GameWindow.h"


/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Border::Border(char position, GameWindow* window) {

	if (position == 'l' or position == 'r') {
		o_width = 50.f;
		o_height = window->GetHeight();
	}
	if (position == 'u' or position == 'd') {
		o_width = window->GetWidth();
		o_height = 50.f;

	}
	o_shape = new RectangleShape(Vector2f(o_width, o_height));
	o_shape->setOrigin(0.5f, 0.5f);
	o_life = NULL;
}