#include "GameObject.h"
#include "GameWindow.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

GameObject::GameObject(char shape) {
	o_height = 0;
	o_width = 0;
	o_posX = 0.f;
	o_posY = 0.f;
	o_directionX = 0.f;
	o_directionY = 0.f;
	
	if (shape == 'c') {
		o_shape = new CircleShape(1.f);
	}
	else if (shape == 'r') {
		o_shape = new RectangleShape(Vector2f(1.f, 1.f));
	}
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

void GameObject::Move(float deltaTime) {
	o_posX += o_directionX * deltaTime * 100.0f;
	o_posY += o_directionY * deltaTime * 100.0f;
	o_shape->setPosition(o_posX, o_posY);
}

void GameObject::SetOrigin(float x, float y){
	o_shape->setOrigin(x, y);
}

void GameObject::SetOrientation(int x, int y)
{
	float	orientation;

	orientation = -atan2(x - o_posX, y - o_posY) * 180 / 3.14159;
	o_shape->setRotation(orientation);
}

void GameObject::SetDirection(float dirX, float dirY) {
	o_directionX = dirX / sqrt(pow(dirX,2)+pow(dirY,2));
	o_directionY = dirY / sqrt(pow(dirX, 2) + pow(dirY, 2));

}

char GameObject::IsColliding(GameObject* Object) {
	if (o_posY+o_height/2 >= Object->o_posY-Object->o_height/2 and o_posY-o_height / 2 <= Object->o_posY+Object->o_height/2 and o_posX+o_width/2 >=Object->o_posX-Object->o_width/2 and o_posX-o_width/2 <= Object->o_posX+Object->o_width/2) {
		float overlapLR = min(o_posY + o_height / 2, Object->o_posY + Object->o_height / 2) - max(o_posY - o_height / 2, Object->o_posY - Object->o_height / 2);
		float overlapUD = min(o_posX + o_width / 2, Object->o_posX + Object->o_width / 2) - max(o_posX - o_width / 2, Object->o_posX - Object->o_width / 2);
		//cout << overlapLR << "  ud:" << overlapUD << endl;
		if (overlapLR > overlapUD) {
			if (o_posX + o_width / 2 >= Object->o_posX - Object->o_width / 2 and o_posX <= Object->o_posX) {
				cout << "left" << endl;
				return 'l';
			}
			else {
				cout << "right" << endl;
				return 'r';
			}
		}
		else if (overlapLR < overlapUD) {
			if (o_posY + o_height / 2 >= Object->o_posY - Object->o_height / 2 and o_posY <= Object->o_posY) {
				cout << "UP"<<endl;
				return 'u';
			}
			else {
				cout << "down" << endl;
				return 'd';
			}
		}
		
		
		return 'u';
	}

}