#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

GameObject::GameObject(char shape) {
	o_height = 0;
	o_width = 0;
	o_posX = 0.f;
	o_posY = 0.f;
	
	if (shape == 'c') {
		o_shape = new CircleShape(20.f);
	}
	else if (shape == 'r') {
		o_shape = new RectangleShape(Vector2f(120.f, 50.f));
	}
}

void GameObject::setPos(float posX, float posY) {
	o_posX = posX;
	o_posY = posY;
	o_shape->setPosition(posX, posY);
}

void GameObject::setSize(int width, int height) {
	o_width = width;
	o_height = height;
}