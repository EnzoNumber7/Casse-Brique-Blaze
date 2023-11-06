#include "GameWindow.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

GameWindow::GameWindow(){
	this->w_width = 800;
	this->w_height = 600;
	this->w_name = "SFML Brick Breaker";

	this->w_window = new sf::RenderWindow(sf::VideoMode(this->w_width, this->w_height), this->w_name);
}

void	GameWindow::DrawObject(GameObject *gameObject){
	this->w_window->draw(*gameObject->o_shape);
}

void	GameWindow::RefreshScreen(){
	this->w_window->clear();
}