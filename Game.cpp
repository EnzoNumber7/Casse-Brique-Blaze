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
	g_ballNum = 99;
	g_currentBall = new GameObject('c');
	g_currentBall->SetSize(20, 20);
	g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight());
	g_currentBall->SetOrigin(0.5f, 0.5f);
	g_currentBall->SetDirection(Mouse::getPosition(*g_window->w_window).x - g_currentBall->o_posX, Mouse::getPosition(*g_window->w_window).y - g_currentBall->o_posY);
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
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){
				if (!g_currentBall){
					if (Game::NewBall() == 1) {
						std::cout << "No more balls available" << std::endl;
						g_isRunning = false;
					}
				}
			}
        }
}

void	Game::RefreshWindow(){
	g_window->w_window->clear();
	if (g_currentBall)
		g_window->DrawObject(g_currentBall);
	if (!g_bricks.empty())
		for (int i = 0; i < g_bricksNum; ++i)
			g_window->DrawObject(g_bricks.at(i));
	g_window->DrawObject(g_canon);
	g_window->w_window->display();
}

int	Game::NewBall(){
	if (g_remainingBalls.empty())
		return (1);
	g_currentBall = g_remainingBalls.at(0);
	g_remainingBalls.pop_back();
	g_currentBall->SetSize(20, 20);
	g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight());
	g_currentBall->SetOrigin(0.5f, 0.5f);
	g_currentBall->SetDirection(Mouse::getPosition(*g_window->w_window).x - g_currentBall->o_posX, Mouse::getPosition(*g_window->w_window).y - g_currentBall->o_posY);
}

void	Game::GenerateTerrain(){
	g_bricksNum = 10;
	for (int i = 0; i < g_ballNum - 1; i++) {
		GameObject* brick = new GameObject('r');
		brick->SetSize(50, 50);
		brick->SetPos(50 + (i * 50 + (10 * i)), 50);
		brick->SetOrigin(0.5f, 0.5f);
		g_bricks.push_back(brick);
	}
}

void	Game::GenerateCanon(){
	GameObject* g_canon = new GameObject('r');
	g_canon->SetSize(50, 100);
	g_canon->SetPos(g_window->GetWidth() / 2, g_window->GetHeight());
}


void	Game::SetBorder(GameObject* border, char id){
	switch (id) {
	case('l'):
		border->SetSize(100, g_window->w_height);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(-50, g_window->w_height / 2);
		break;
	case('u'):
		border->SetSize(g_window->w_width, 100);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width / 2, -50);
		break;
	case('r'):
		border->SetSize(100, g_window->w_height);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width + 50, g_window->w_height / 2);
		break;
	case('d'):
		border->SetSize(g_window->w_width, 100);
		border->SetOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width / 2, g_window->w_height + 50);
		break;
	}
}

void	Game::GenerateBorders(){
	GameObject* leftWall = new GameObject('r');
	GameObject* rightWall = new GameObject('r');
	GameObject* upWall = new GameObject('r');
	GameObject* downWall = new GameObject('r');

	SetBorder(leftWall, 'l');
	SetBorder(upWall, 'u');
	SetBorder(rightWall, 'r');
	SetBorder(downWall, 'd');

	g_borders[0] = leftWall;
	g_borders[1] = upWall;
	g_borders[2] = rightWall;
	g_borders[3] = downWall;
}

void	Game::CloseWindow(){
	g_window->w_window->close();
}

void Game::DestroyBall() {
	delete g_currentBall;
}