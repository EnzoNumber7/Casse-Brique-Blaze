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

void	GameWindow::SetBorder(GameObject *border, char id){
	switch(id){
	case('l'):
		border->SetSize(100, w_height);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(-50, w_height / 2);
		break;
	case('u'):
		border->SetSize(w_width, 100);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(w_width / 2, -50);
		break;
	case('r'):
		border->SetSize(100, w_height);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(w_width + 50, w_height / 2);
		break;
	case('d'):
		border->SetSize(w_width, 100);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(w_width / 2, w_height + 50);
		break;
	}
}

void	GameWindow::GenerateBorders() {
	GameObject *leftWall = new GameObject('r');
	GameObject *rightWall = new GameObject('r');
	GameObject *upWall = new GameObject('r');
	GameObject *downWall = new GameObject('r');

	SetBorder(leftWall, 'l');
	SetBorder(upWall, 'u');
	SetBorder(rightWall, 'r');
	SetBorder(downWall, 'd');

	w_borders[0] = leftWall;
	w_borders[1] = upWall;
	w_borders[2] = rightWall;	
	w_borders[3] = downWall;
}

void	GameWindow::RefreshScreen(){
	w_window->clear();
}

float GameWindow::GetWidth() {
	return w_width;
}

float GameWindow::GetHeight() {
	return w_height;
}