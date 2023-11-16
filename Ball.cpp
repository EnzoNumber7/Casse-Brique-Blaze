#include "Ball.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include "math.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define SPEED 300.0f

using namespace std;
using namespace math;

Ball::Ball(sf::Sprite *sprite) : GameObject(sprite) {
	//o_shape = new CircleShape(10.f);
	o_width = 20.f;
	o_height = 20.f;
	o_sprite.setOrigin(10.0f, 10.0f);
	isMoving = false;
}

void Ball::Move(float deltaTime) {
	o_posX += o_directionX * deltaTime * SPEED;
	o_posY += o_directionY * deltaTime * SPEED;
	o_sprite.setPosition(o_posX, o_posY);
}

void Ball::Rebound(CollisionSide direction, float deltaTime) {
	if (direction == Left or direction == Right) {
		o_directionX = -o_directionX;
	}
	else if (direction == Up or direction == Down) {
		o_directionY = -o_directionY;
	}
	else if (direction == Diagonal) {
		o_directionY = -o_directionY;
		o_directionX = -o_directionX;
	}
}

void Ball::OnCollisionEnter(const GameObject& Object, float deltaTime) {
	//cout << "ENTER" << endl;
	o_shouldMove = false;
	float overlapLR = min(o_posY + o_height / 2, Object.o_posY + Object.o_height / 2) - max(o_posY - o_height / 2, Object.o_posY - Object.o_height / 2);
	float overlapUD = min(o_posX + o_width / 2, Object.o_posX + Object.o_width / 2) - max(o_posX - o_width / 2, Object.o_posX - Object.o_width / 2);
	overlapLR = RoundFloat(overlapLR, 3);
	overlapUD = RoundFloat(overlapUD, 3);
	if (overlapLR > overlapUD) {
		if (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX and o_lastSide != Left) {
			Rebound(Left,deltaTime);
			o_lastSide = Left;
		}
		else if (o_posX - o_width / 2 <= Object.o_posX + Object.o_width / 2 and o_posX >= Object.o_posX and o_lastSide != Right) {
			Rebound(Right, deltaTime);
			o_lastSide = Right;
		}
	}
	else if (overlapLR < overlapUD) {
		if (o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY and o_lastSide != Up) {
			Rebound(Up, deltaTime);
			o_lastSide = Up;
		}
		else if (o_posY - o_height / 2 <= Object.o_posY + Object.o_height / 2 and o_posY >= Object.o_posY and o_lastSide != Down){
			Rebound(Down, deltaTime);
			o_lastSide = Down;
		}
	}
	else if (overlapLR == overlapUD) {
		Rebound(Diagonal, deltaTime);
		o_lastSide = Diagonal;
	}

}

void Ball::OnCollisionStay(float deltaTime) {
	//std::cout << "STAY" << std::endl;
	Move(deltaTime);
}
