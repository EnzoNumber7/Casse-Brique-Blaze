#pragma once

#include <SFML/Graphics.hpp>
class GameWindow;

class GameObject {

private:
	float			o_width;
	float			o_height;
	bool			o_InCollision;
	char			o_collideDirection;

public:
	sf::Shape*		o_shape;
	float			o_posX;
	float			o_posY;
	float			o_directionX;
	float			o_directionY;

	GameObject();
	~GameObject();

	void			ChangeCollideBool();
	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
	void			SetSize(float width, float height);
	void			SetOrientation(int x, int y);
	void			SetDirection(float dirX, float dirY);
	char			IsColliding(GameObject* Object);
	bool			CheckCollision( GameObject* Object, float deltaTime);
	char			virtual OnCollisionEnter(const GameObject& Object);
	void			virtual OnCollisionStay(char direction, float deltaTime);
	void			virtual OnCollisionExit();
};

