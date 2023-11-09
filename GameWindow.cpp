#include "GameWindow.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

GameWindow::GameWindow(){
	w_width = 800.f;
	w_height = 600.f;
	w_name = "SFML Brick Breaker";

	w_window = new sf::RenderWindow(sf::VideoMode(w_width, w_height), w_name);
}

void	GameWindow::DrawObject(GameObject *gameObject){
	w_window->draw(*gameObject->o_shape);
}

void	GameWindow::RefreshScreen(){
	w_window->clear();
}

float GameWindow::GetWidth() {
	return (float)w_width;
}

float GameWindow::GetHeight() {
	return (float)w_height;
}