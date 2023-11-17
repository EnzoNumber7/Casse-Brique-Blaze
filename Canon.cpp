#include "Canon.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Canon::Canon(sf::Sprite* sprite) : GameObject(sprite) {
	o_sprite.setOrigin(25.f, 0.f);
	o_width = 50.f;
	o_height = 100.f;
}

void	Canon::FollowMouse(GameWindow *window) {
	if (Mouse::getPosition(*window->w_window).y < o_posY - 50) 
		SetOrientation(Mouse::getPosition(*window->w_window).x, Mouse::getPosition(*window->w_window).y);
}
