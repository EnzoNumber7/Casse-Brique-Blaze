#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

GameObject::GameObject() {
	o_shape = NULL;
	o_height = 0;
	o_width = 0;
	o_posX = 0.f;
	o_posY = 0.f;
	o_directionX = 0.f;
	o_directionY = 0.f;
	o_InCollision = false;
	o_life = NULL;
	o_shouldMove = true;
	o_lastSide = None;
}

void GameObject::SetPos(float posX, float posY) {
	o_posX = posX;
	o_posY = posY;
	o_shape->setPosition(posX, posY);
}

void GameObject::SetColor(int r, int g, int b) {
	o_shape->setFillColor(Color(r, g, b));
}

void GameObject::SetOrientation(int x, int y)
{
	float	orientation;

	orientation = -atan2(x - o_posX, y - o_posY) * 180 / 3.14159f;
	o_shape->setRotation(orientation);
}

void GameObject::SetDirection(float dirX, float dirY) {
	o_directionX = dirX / (float)sqrt(pow(dirX,2)+pow(dirY,2));
	o_directionY = dirY / (float)sqrt(pow(dirX, 2) + pow(dirY, 2));

}

void GameObject::DecreaseLife(GameObject* Object, int value){
	if (Object->o_life != NULL)
		Object->o_life = Object->o_life - value;
	switch(o_life){
		case (2):
			o_shape->setFillColor(sf::Color::Yellow);
			break;
		case (1):
			o_shape->setFillColor(sf::Color::Red);
			break;
	}
}

void GameObject::ChangeCollideBool() {
	o_InCollision = not o_InCollision;
}

bool GameObject::CheckCollision(GameObject* Object, float deltaTime) {
	bool collision = (o_posX-o_width/2 <= Object->o_posX + Object->o_width/2 and o_posX + o_width/2 >= Object->o_posX - Object->o_width/2) and (o_posY - o_height / 2 <= Object->o_posY + Object->o_height / 2 and o_posY + o_height / 2 >= Object->o_posY - Object->o_height / 2);
	if (collision) {
		if (not Object->o_InCollision) {
			OnCollisionEnter(*Object, deltaTime);
			Object->ChangeCollideBool();
		}
		else {
			OnCollisionStay(deltaTime);
		}
	}
	else {
		if (Object->o_InCollision) {
			OnCollisionExit();
			Object->ChangeCollideBool();
			Object->DecreaseLife(Object, 1);
		}
	}

	if (collision) {
		return 1;
	}
	else return 0;
}

void GameObject::OnCollisionEnter(const GameObject& Object, float deltaTime) {
	o_shouldMove = false;
	char direction;
	float overlapLR = min(o_posY + o_height / 2, Object.o_posY + Object.o_height / 2) - max(o_posY - o_height / 2, Object.o_posY - Object.o_height / 2);
	float overlapUD = min(o_posX + o_width / 2, Object.o_posX + Object.o_width / 2) - max(o_posX - o_width / 2, Object.o_posX - Object.o_width / 2);
	if (overlapLR > overlapUD) {
		if (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX and o_lastSide != Left) {
			o_directionX = -o_directionX;
			o_lastSide = Left;
		}
		else if (o_lastSide != Left) {
			o_directionX = -o_directionX;
			o_lastSide = Right;
		}
	}
	else if (overlapLR < overlapUD) {
		if (o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY and o_lastSide != Up) {
			o_directionY = -o_directionY;
			o_lastSide = Up;
		}
		else if (o_lastSide != Down) {
			o_directionY = -o_directionY;
			o_lastSide = Down;
		}
	}
	else  {
		o_directionY = -o_directionY;
		o_directionX = -o_directionX;
		o_lastSide = Diagonal;
	}
	
}

void GameObject::OnCollisionStay(float deltaTime){
	
}

void GameObject::OnCollisionExit(){
	cout << "EXIT" << endl;
	o_shouldMove = true;
}

GameObject::~GameObject() {

}