#include "Ball.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Ball::Ball() {
	o_shape = new CircleShape(1.f);
	o_shape->setOrigin(0.5f, 0.5f);
	isMoving = false;
}

void Ball::Move(float deltaTime) {
	o_posX += o_directionX * deltaTime * 75.0f;
	o_posY += o_directionY * deltaTime * 75.0f;
	o_shape->setPosition(o_posX, o_posY);
}

void Ball::Rebound(char direction, float deltaTime) {
	if (direction == 'l' or direction == 'r') {
		o_directionX = -o_directionX;
		Move(deltaTime);
	}
	else if (direction == 'u' or direction == 'd') {
		o_directionY = -o_directionY;
		Move(deltaTime);
	}
	else if (direction == 'c') {
		o_directionY = -o_directionY;
		o_directionX = -o_directionX;
		Move(deltaTime);
	}
}

void Ball::OnCollisionStay(char direction, float deltaTime) {
	Rebound(direction, deltaTime);
}
