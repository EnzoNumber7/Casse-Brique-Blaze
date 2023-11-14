#pragma once

#include <SFML/Graphics.hpp>

enum CollisionSide { Left, Right, Up, Down, Diagonal, None };
class GameWindow;

class GameObject {

private:
	bool			o_InCollision;

public:
	sf::Shape*		o_shape;
	float			o_width;
	float			o_height;
	float			o_posX;
	float			o_posY;
	float			o_directionX;
	float			o_directionY;
	float			o_angle;
	int				o_life;
	bool			o_shouldMove;
	CollisionSide   o_lastSide;

	GameObject();
	~GameObject();

	void			ChangeCollideBool();
	void			ResetAngle();
	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
	void			SetOrientation(int x, int y);
	void			SetDirection(float angle);
	void			DecreaseLife(GameObject* Object, int value);
	bool			CheckCollision( GameObject* Object, float deltaTime);
	void			virtual OnCollisionEnter(const GameObject& Object, float deltaTime);
	void			virtual OnCollisionStay(float deltaTime);
	void			virtual OnCollisionExit();
};

