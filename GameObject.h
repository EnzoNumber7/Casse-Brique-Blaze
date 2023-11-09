#pragma once

#include <SFML/Graphics.hpp>
class GameWindow;

class GameObject {

private:
	float			o_width;
	float			o_height;
	float			o_directionX;
	float			o_directionY;

public:
	sf::Shape*		o_shape;
	float			o_posX;
	float			o_posY;

					GameObject(char shape);

	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
	void			SetSize(float width, float height);
	void			Move(float deltaTime);
	void			SetOrientation(int x, int y);
	void			SetDirection(float dirX, float dirY);
	void			SetOrigin(float x, float y);
	char			IsColliding(GameObject* Object);
	void	 		Rebound(char direction, float deltaTime);
};

