#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject{
	float		o_posX;

private:
	float		o_posY;
	int			o_width;
	int			o_height;

public:
	Shape*		o_shape;

	GameObject(char shape);

	void	ChangeColor();
	void	setPos(float posX, float posY);
	void	setSize(int width, int height);
};

