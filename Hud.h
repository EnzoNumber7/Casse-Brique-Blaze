#pragma once

#include <SFML/Graphics.hpp>
#include "GameWindow.h"
class Hud
{
private:

	// Main Attributes
	sf::Font					h_font;

public:

	sf::Text					h_balls;

	Hud();

	//Main Methods

	void	StartGame(GameWindow* window);
	void	DrawHud(GameWindow *window, int ball_num);
};

