#pragma once
#include "GameObject.h"

enum CollisionSides { Left, Right, Up, Down, DiagonalUL, DiagonalUR, DiagonalDL, DiagonalDR, None};
class Collision
{
private:
	GameObject*			c_FirstCollider;
	GameObject*			c_SecondCollider;
	CollisionSides		c_side;

public:
						Collision(GameObject* Collider1, GameObject* Collider2);
						~Collision();
	void				DetectSide();
	void				DetectDiagonal();
	void				RectRebound();
	void				CircleRebound();
};

