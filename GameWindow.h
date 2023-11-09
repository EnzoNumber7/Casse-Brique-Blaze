#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;
using namespace sf;

class GameWindow
{
private:
	const char*			w_name;

public:

	float				w_width;
	float				w_height;
	RenderWindow		*w_window;

	void				DrawObject(GameObject *gameObject);
	void				RefreshScreen();   
	float				GetWidth();
	float				GetHeight();

	GameWindow();
};

