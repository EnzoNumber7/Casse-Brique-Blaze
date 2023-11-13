#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "GameWindow.h"
#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Canon.h"
#include "Border.h"

Game::Game(){
	g_window = new GameWindow();
	g_deltaTime = 0.f;
	g_isRunning = true;
	g_ballNum = 50;
	g_currentBall = new Ball();
	g_currentBall->SetSize(20, 20);
	g_currentBall->SetPos(g_window->GetWidth() / 2 - 10, g_window->GetHeight() - 40);
	g_canon = NULL;
	g_bricksNum = NULL;
	*g_borders = NULL;
	if (!g_font.loadFromFile("rsrc/font.ttf"))
	{
		std::cout << "Error Loading font" << std::endl;
		exit(1);
	}
	g_screenBalls.setFont(g_font);
	g_screenBalls.setCharacterSize(24);
	g_screenBalls.setFillColor(sf::Color::Green);
	g_screenBalls.setStyle(sf::Text::Bold);
	g_screenBalls.setPosition(760, 0);
}

void Game::HandleEvents(){
	Event event;
        while (g_window->w_window->pollEvent(event))
        {
			if (event.type == Event::Closed)
				CloseWindow();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){
				if (!g_currentBall){
					std::cout << "No more balls available" << std::endl;
					g_isRunning = false;
				}
				else{
					SendBall();
				}
			}
        }
}

void Game::RefreshWindow(){
	g_window->RefreshScreen();
	if (g_currentBall && g_currentBall->isMoving)
		g_window->DrawObject(g_currentBall);
	if (!g_bricks.empty())
		for (int i = 0; i < g_bricksNum; ++i) {
			g_window->DrawObject(g_bricks.at(i));
		}
	for (int j = 0; j < 4; ++j)
		g_window->DrawObject(g_borders[j]);
	g_window->DrawObject(g_canon);
	DrawHUD();
	g_window->w_window->display();
}

void Game::DrawHUD(){
	g_screenBalls.setString(std::to_string(g_ballNum));
	g_window->w_window->draw(g_screenBalls);
}

int	Game::NewBall(){
	if (g_remainingBalls.empty()) {
		std::cout << "Unlucky ! You lost with " << g_bricksNum << " Bricks Remaining !" << std::endl;
		return 1;
	}
	if (g_bricks.empty()) {
		std::cout << "Good job ! You won with " << g_ballNum << " Balls Remaining !" << std::endl;
		return 1;
	}
	g_ballNum--;
	g_currentBall = g_remainingBalls.at(g_remainingBalls.size() - 1);
	g_remainingBalls.pop_back();
	g_currentBall->SetSize(20, 20);
	g_currentBall->SetPos(g_window->GetWidth() / 2 - 10, g_window->GetHeight() - 40);
	g_canon->SetColor(0, 255, 0);
	std::cout << g_ballNum << " Balls Remaining." << std::endl;
	return 0;
}

void	Game::SendBall(){
	if (g_currentBall->isMoving == false) {
		g_currentBall->SetDirection(Mouse::getPosition(*g_window->w_window).x - g_currentBall->o_posX, Mouse::getPosition(*g_window->w_window).y - g_currentBall->o_posY);
		g_currentBall->isMoving = true;
		g_canon->SetColor(255, 0, 0);
	}
}

void	Game::GenerateBalls () {
	for (int i = 0; i < g_ballNum - 1; i++) {
		Ball* ball = new Ball();
		g_remainingBalls.push_back(ball);
	}
}

void	Game::GenerateTerrain(){
	g_bricksNum = 4;
	for (float i = 0; i <= g_bricksNum - 1; i++) {
		Brick* brick = new Brick();
		brick->SetSize(50, 50);
		brick->SetPos(250 + (i * 50 + (10 * i)), 250);
		g_bricks.push_back(brick);
	}
}

void	Game::GenerateCanon(){
	g_canon = new Canon();
	g_canon->SetColor(0, 255, 0);
	g_canon->SetSize(50, 100);
	g_canon->SetPos(g_window->GetWidth() / 2, g_window->GetHeight());
	g_canon->SetDirection(0, -1);
}


void	Game::SetBorder(Border* border, char id){
	switch (id) {
	case('l'):
		border->SetSize(100, g_window->w_height);
		border->o_shape->setOrigin(0.5f, 0.5f);
		border->SetPos(-50, g_window->w_height / 2);
		break;
	case('u'):
		border->SetSize(g_window->w_width, 100);
		border->o_shape->setOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width / 2, -50);
		break;
	case('r'):
		border->SetSize(100, g_window->w_height);
		border->o_shape->setOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width + 50, g_window->w_height / 2);
		break;
	case('d'):
		border->SetSize(g_window->w_width, 100);
		border->o_shape->setOrigin(0.5f, 0.5f);
		border->SetPos(g_window->w_width / 2, g_window->w_height + 50);
		break;
	}
}

void	Game::GenerateBorders(){
	Border* leftWall = new Border();
	Border* rightWall = new Border();
	Border* upWall = new Border();
	Border* downWall = new Border();

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

void Game::ClearBricks() {
	Brick* brick;
	if (g_bricks.empty() == false) {
		for (int i = 0; i < g_bricksNum; i++) {
			if (g_bricks.at(i)->o_life == 0)
			{
				brick = g_bricks.at(i);
				g_bricks.erase(g_bricks.begin() + i);
				delete brick;
				g_bricksNum--;
			}
		}
	}
}