#pragma once
#include <SFML/Graphics.hpp>

class GameObject;
using namespace sf;

class GameWindow
{
	int					w_width;
	int					w_height;
	const char*			w_name;

public:
	RenderWindow		*w_window;

	void				DrawObject(GameObject *gameObject);
	void				RefreshScreen();

	GameWindow();
};

