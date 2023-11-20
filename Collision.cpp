#include "Collision.h"
#include "math.h"
#include <iostream>

using namespace math;
using namespace std;

Collision::Collision(GameObject* Collider1, GameObject* Collider2) {
	c_side = None;
	c_FirstCollider = Collider1;
	c_SecondCollider = Collider2;
}

void Collision::DetectSide() {
	float overlapLR = min(c_FirstCollider->o_posY + c_FirstCollider->o_height / 2, c_SecondCollider->o_posY + c_SecondCollider->o_height / 2) - max(c_FirstCollider->o_posY - c_FirstCollider->o_height / 2, c_SecondCollider->o_posY - c_SecondCollider->o_height / 2);
	float overlapUD = min(c_FirstCollider->o_posX + c_FirstCollider->o_width / 2, c_SecondCollider->o_posX + c_SecondCollider->o_width / 2) - max(c_FirstCollider->o_posX - c_FirstCollider->o_width / 2, c_SecondCollider->o_posX - c_SecondCollider->o_width / 2);
	overlapLR = RoundFloat(overlapLR, 3);
	overlapUD = RoundFloat(overlapUD, 3);
	if (overlapLR > overlapUD) {
		if (c_FirstCollider->o_posX + c_FirstCollider->o_width / 2 >= c_SecondCollider->o_posX - c_SecondCollider->o_width / 2 and c_FirstCollider->o_posX <= c_SecondCollider->o_posX and c_side != Left) {
			//Rebound();
			c_side = Left;
		}
		else if (c_FirstCollider->o_posX - c_FirstCollider->o_width / 2 <= c_SecondCollider->o_posX + c_SecondCollider->o_width / 2 and c_FirstCollider->o_posX >= c_SecondCollider->o_posX and c_side != Right) {
			//Rebound();
			c_side = Right;
		}
	}
	else if (overlapLR < overlapUD) {
		if (c_FirstCollider->o_posY + c_FirstCollider->o_height / 2 >= c_SecondCollider->o_posY - c_SecondCollider->o_height / 2 and c_FirstCollider->o_posY <= c_SecondCollider->o_posY and c_side != Up) {
			//Rebound();
			c_side = Up;
		}
		else if (c_FirstCollider->o_posY - c_FirstCollider->o_height / 2 <= c_SecondCollider->o_posY + c_SecondCollider->o_height / 2 and c_FirstCollider->o_posY >= c_SecondCollider->o_posY and c_side != Down) {
			//Rebound();
			c_side = Down;
		}
	}
	else if (overlapLR == overlapUD and c_side != DiagonalDL and c_side != DiagonalDR and c_side != DiagonalUL and c_side != DiagonalUR) {
		DetectDiagonal();
	}
}

/*void Collision::DetectDiagonal() {
		// On vérifie sur quelle diagonal on collide, puis on verifie que les direction n'ont pas déjà été inverser par une collision précédente
		if ((o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY) and (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX and o_lastSide)) {
			if (o_directionY < 0 and o_directionX > 0) { // La direction en Y a déjà été inversé, ainsi on veut juste inverser X, ce qui revient a collide a gauche
				Rebound(Left, deltaTime);
			}
			if (o_directionX < 0 and o_directionY > 0) {
				Rebound(Up, deltaTime);
			}
			else if (o_directionX > 0 and o_directionY > 0) {
				Rebound(Diagonal, deltaTime);
			}
		}
		if ((o_posY + o_height / 2 >= Object.o_posY - Object.o_height / 2 and o_posY <= Object.o_posY) and (o_posX - o_width / 2 <= Object.o_posX + Object.o_width / 2 and o_posX >= Object.o_posX)) {
			if (o_directionY < 0 and o_directionX < 0) {
				Rebound(Left, deltaTime);
			}
			if (o_directionX > 0 and o_directionY > 0) {
				Rebound(Up, deltaTime);
			}
			else if (o_directionY > 0 and o_directionX < 0) {
				cout << o_directionY << endl; // Verif si on touche pas un truc avant 
				Rebound(Diagonal, deltaTime);
			}
		}
		if ((o_posY - o_height / 2 <= Object.o_posY + Object.o_height / 2 and o_posY >= Object.o_posY) and (o_posX - o_width / 2 <= Object.o_posX + Object.o_width / 2 and o_posX >= Object.o_posX)) {
			if (o_directionY > 0 and o_directionX < 0) {
				Rebound(Left, deltaTime);
			}
			if (o_directionX > 0 and o_directionY < 0) {
				Rebound(Up, deltaTime);
			}
			else if (o_directionY < 0 and o_directionX < 0) {
				Rebound(Diagonal, deltaTime);
			}
		}
		if ((o_posY - o_height / 2 <= Object.o_posY + Object.o_height / 2 and o_posY >= Object.o_posY) and (o_posX + o_width / 2 >= Object.o_posX - Object.o_width / 2 and o_posX <= Object.o_posX)) {
			if (o_directionY > 0 and o_directionX > 0) {
				Rebound(Left, deltaTime);
			}
			if (o_directionX < 0 and o_directionY < 0) {
				Rebound(Up, deltaTime);
			}
			else if (o_directionY < 0 and o_directionX > 0) {
				Rebound(Diagonal, deltaTime);
			}
		}
		o_lastSide = Diagonal;

}*/