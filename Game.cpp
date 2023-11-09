#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "GameWindow.h"
#include "GameObject.h"

Game::Game(){
	g_window = new GameWindow();
	g_window->GenerateBorders();
	g_deltaTime = 0.f;
	g_isRunning = true;
	g_ballNum = 3;
	g_currentBall = new GameObject('c');
	for(int i = 0; i < g_ballNum - 1; i++){
		GameObject  *ball = new GameObject('c');
		g_remainingBalls.push_back(ball);
	}
}

void	Game::HandleEvents(){
	Event event;
        while (g_window->w_window->pollEvent(event))
        {
			if (event.type == Event::Closed)
				CloseWindow();
			if (event.key.scancode == sf::Keyboard::Scan::Escape){
				if (Game::NewBall() == 1){
					std::cout << "No more balls available" << std::endl;
					g_isRunning = false;
				}
			}
        }
}

void	Game::RefreshWindow(){
	if (g_currentBall)
		g_window->DrawObject(g_currentBall);
}

int	Game::NewBall(){
	if (!g_remainingBalls.at(0))
		return (1);
	g_currentBall = g_remainingBalls.at(0);
	g_remainingBalls.pop_back();
	g_currentBall->SetSize(50, 50);
	g_currentBall->SetPos(0, 0);
	g_currentBall->SetOrigin(0.5f, 0.5f);
	//g_currentBall->SetDirection(Mouse::getPosition(*g_window->w_window).x, Mouse::getPosition(*g_window->w_window).y);
}

void	Game::CloseWindow(){
	g_window->w_window->close();
}