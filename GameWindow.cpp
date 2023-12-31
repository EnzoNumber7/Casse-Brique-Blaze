#include "GameWindow.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

GameWindow::GameWindow(){
	w_width = 1920.f;
	w_height = 1080.f;
	w_name = "Minecraft Brick Breaker";

	w_window = new sf::RenderWindow(sf::VideoMode((unsigned int)w_width, (unsigned int)w_height), w_name);
	sf::View view(sf::Vector2f(960, 540), sf::Vector2f(1920, 1080));
	w_window->setView(view);
}

/*
---------------------------------------------------------------------------------
|				Here are all the get methods									|
---------------------------------------------------------------------------------
*/

float GameWindow::GetWidth() {
	return (float)w_width;
}

float GameWindow::GetHeight() {
	return (float)w_height;
}

/*
---------------------------------------------------------------------------------
|				Here are all the main methods									|
---------------------------------------------------------------------------------
*/

void	GameWindow::DrawObject(GameObject *gameObject){
	w_window->draw(gameObject->o_sprite);
}

void	GameWindow::RefreshScreen(){
	w_window->clear();
}

GameWindow::~GameWindow() {
	delete w_window;
}