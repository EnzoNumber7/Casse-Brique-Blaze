#pragma once

#include <SFML/Graphics.hpp>
class GameWindow;

class GameObject {

private:
	float			o_width;
	float			o_height;

public:
	sf::Shape*		o_shape;
	float			o_posX;
	float			o_posY;
	float			o_directionX;
	float			o_directionY;

	GameObject();
	~GameObject();

	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
	void			SetSize(float width, float height);
	void			SetOrientation(int x, int y);
	void			SetDirection(float dirX, float dirY);
	char			IsColliding(GameObject* Object);
};

