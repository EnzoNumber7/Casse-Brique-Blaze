#pragma once

#include <SFML/Graphics.hpp>
class GameWindow;

using namespace sf;

class GameObject{

private:
	float		o_posX;
	float		o_posY;
	int			o_width;
	int			o_height;
	float		o_directionX;
	float		o_directionY;

public:
	Shape*		o_shape;

	GameObject(char shape);

	void		SetColor(int r, int g, int b);
	void		SetPos(float posX, float posY);
	void		SetSize(int width, int height);
	void		Move(float deltaTime);
	void		SetOrientation(int x, int y);
	void		SetDirection(float dirX, float dirY);
	void		SetOrigin(float x, float y);
	char		IsColliding(GameObject* Object);
};

