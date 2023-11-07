#pragma once
#include <SFML/Graphics.hpp>

class GameObject;
using namespace sf;

class GameWindow
{
private:
	float				w_width;
	float				w_height;
	const char*			w_name;

public:
	RenderWindow		*w_window;
	GameObject*			w_borders;

	void				DrawObject(GameObject *gameObject);
	void				RefreshScreen();
	float				GetWidth();
	float				GetHeight();

	GameWindow();
};

