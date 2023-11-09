#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;
using namespace sf;

class GameWindow
{
private:
	float				w_width;
	float				w_height;
	const char*			w_name;

	void				SetBorder(GameObject* border, char id);

public:
	RenderWindow		*w_window;
	GameObject			*w_borders[4];

	void				DrawObject(GameObject *gameObject);
	void				RefreshScreen();   
	float				GetWidth();
	float				GetHeight();
	void				GenerateBorders();

	GameWindow();
};

