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
	o_collideDirection = 'n';
	o_life = NULL;
}

void GameObject::SetPos(float posX, float posY) {
	o_posX = posX;
	o_posY = posY;
	o_shape->setPosition(posX, posY);
}

void GameObject::SetSize(float width, float height) {
	o_width = width;
	o_height = height;
	o_shape->setScale(width, height);
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
	if (Object->o_life != NULL) {
		Object->o_life = Object->o_life - value;
		std::cout << Object->o_life << std::endl;
		//if (Object->o_life <= 0)
			//delete Object;
	}
}

char GameObject::IsColliding(GameObject* Object) {
	if (o_posY+o_height/2 >= Object->o_posY-Object->o_height/2 and o_posY-o_height / 2 <= Object->o_posY+Object->o_height/2 and o_posX+o_width/2 >=Object->o_posX-Object->o_width/2 and o_posX-o_width/2 <= Object->o_posX+Object->o_width/2) {
		float overlapLR = min(o_posY + o_height / 2, Object->o_posY + Object->o_height / 2) - max(o_posY - o_height / 2, Object->o_posY - Object->o_height / 2);
		float overlapUD = min(o_posX + o_width / 2, Object->o_posX + Object->o_width / 2) - max(o_posX - o_width / 2, Object->o_posX - Object->o_width / 2);
		if (overlapLR > overlapUD) {
			if (o_posX + o_width / 2 >= Object->o_posX - Object->o_width / 2 and o_posX <= Object->o_posX) {
				return 'l';
			}
			else {
				return 'r';
			}
		}
		else if (overlapLR < overlapUD) {
			if (o_posY + o_height / 2 >= Object->o_posY - Object->o_height / 2 and o_posY <= Object->o_posY) {
				return 'u';
			}
			else {
				return 'd';
			}
		}
		else return 'c';

	}
	return 'n';
}

void GameObject::ChangeCollideBool() {
	o_InCollision = not o_InCollision;
}

bool GameObject::CheckCollision(GameObject* Object, float deltaTime) {
	bool collision = (o_posX-o_width/2 <= Object->o_posX + Object->o_width/2 and o_posX + o_width/2 >= Object->o_posX - Object->o_width/2) and (o_posY - o_height / 2 <= Object->o_posY + Object->o_height / 2 and o_posY + o_height / 2 >= Object->o_posY - Object->o_height / 2);
	if (collision) {
		if (not Object->o_InCollision) {
			o_collideDirection = OnCollisionEnter(*Object);
			Object->ChangeCollideBool();
		}
		else {
			OnCollisionStay(o_collideDirection, deltaTime);
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

char GameObject::OnCollisionEnter(const GameObject& Object) {
	//cout << "ENTER" << endl;
	float overlapLR = min(o_posY + o_height / 2, Object.o_posY + Object.o_height / 2) - max(o_posY - o_height / 2, Object.o_posY - Object.o_height / 2);
	float overlapUD = min(o_posX + o_width / 2, Object.o_posX + Object.o_width / 2) - max(o_posX - o_width / 2, Object.o_posX - Object.o_width / 2);
	if (overlapLR > overlapUD) {
		if (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX) {
			return 'l';
		}
		else {
			return 'r';
		}
	}
	else if (overlapLR < overlapUD) {
		if (o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY) {
			return 'u';
		}
		else {
			return 'd';
		}
	}
	else return 'c';
	
}

void GameObject::OnCollisionStay(char direction, float deltaTime){

}

void GameObject::OnCollisionExit(){
	//cout << "EXIT" << endl;
}

GameObject::~GameObject() {

}