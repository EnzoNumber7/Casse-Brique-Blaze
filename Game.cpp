#include <SFML/Graphics.hpp>
#include <iostream>
#include <errno.h>
#include <SFML/System/Vector2.hpp>

#include "Game.h"

#include "GameWindow.h"
#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Canon.h"
#include "Border.h"
#include "Map.h"
#include "Hud.h"

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Game::Game(){
	g_window = new GameWindow();
	g_menu = true;
	g_deltaTime = 0.f;
	g_isRunning = true;
	g_numSim = 10;

	g_filePath = new std::string();


	g_ballNum = 50;

	g_canon = NULL;
	g_bricksNum = NULL;
	*g_borders = NULL;
	g_hud = new Hud();

	g_map = new Map();

	g_fpsLimit = 1.0f / 120.0f;
}

/* 
---------------------------------------------------------------------------------
|				Here are all the generation methods								|
---------------------------------------------------------------------------------
*/

void Game::GenerateSprites() {
	sf::Texture* menuTexture = new sf::Texture();
	sf::Texture* backgroundTexture = new sf::Texture();
	if (!menuTexture->loadFromFile("rsrc/menu.png") or !backgroundTexture->loadFromFile("rsrc/background.png"))
		std::cout << "Error loading menu or background texture." << std::endl;
	sf::Texture* ballTexture = new sf::Texture();
	sf::Texture* canonTexture = new sf::Texture();
	sf::Texture* brickTexture = new sf::Texture();
	if (!ballTexture->loadFromFile("rsrc/ball.png") or !canonTexture->loadFromFile("rsrc/canon.png") or !brickTexture->loadFromFile("rsrc/brick.png"))
		std::cout << "Error loading object textures." << std::endl;

	sf::Sprite* menuSprite = new sf::Sprite();
	menuSprite->setTexture(*menuTexture);
	g_sprites.push_back(menuSprite);

	sf::Sprite* backgroundSprite = new sf::Sprite();
	backgroundSprite->setTexture(*backgroundTexture);
	g_sprites.push_back(backgroundSprite);

	sf::Sprite* ballSprite = new sf::Sprite();
	ballSprite->setTexture(*ballTexture);
	g_sprites.push_back(ballSprite);

	sf::Sprite* canonSprite = new sf::Sprite();
	canonSprite->setTexture(*canonTexture);
	g_sprites.push_back(canonSprite);

	sf::Sprite* brickSprite = new sf::Sprite();
	brickSprite->setTexture(*brickTexture);
	g_sprites.push_back(brickSprite);
}

void	Game::GenerateTerrain() {
	float	x = 40;
	float	y = 65;
	int		sizeX = g_map->GetWidth();
	int		sizeY = g_map->GetHeight();

	g_bricksNum = 0;
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			if (g_map->m_vstr->at(i).at(j) - 48 != 0) {
				Brick* brick = new Brick(g_map->m_vstr->at(i).at(j) - 48, g_sprites.at(4));
				brick->SetPos(x, y);
				g_bricks.push_back(brick);
				g_bricksNum++;
			}
			x += (60);
		}
		x = 40;
		y += 40;
	}
	if (g_bricks.empty())
	{
		std::cout << "Error Generating Terrain. Terrain must not be empty" << std::endl;
		exit(1);
	}
}

void	Game::SetBorder(Border* border, char id) {
	switch (id) {
	case('l'):
		border->SetBorderPos(-25, g_window->GetHeight() / 2);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('u'):
		border->SetBorderPos(g_window->GetWidth() / 2, -25);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('r'):
		border->SetBorderPos(g_window->GetWidth() + 25, g_window->GetHeight() / 2);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	case('d'):
		border->SetBorderPos(g_window->GetWidth() / 2, g_window->GetHeight() + 25);
		border->o_shape->setOrigin(border->o_width / 2, border->o_height / 2);
		break;
	}
}

void	Game::GenerateBorders() {
	Border* leftWall = new Border('l', g_window);
	Border* rightWall = new Border('r', g_window);
	Border* upWall = new Border('u', g_window);
	Border* downWall = new Border('d', g_window);

	SetBorder(leftWall, 'l');
	SetBorder(upWall, 'u');
	SetBorder(rightWall, 'r');
	SetBorder(downWall, 'd');

	g_borders[0] = leftWall;
	g_borders[1] = upWall;
	g_borders[2] = rightWall;
	g_borders[3] = downWall;
}

void	Game::GenerateBalls() {
	for (int i = 0; i < g_ballNum - 1; i++) {
		Ball* ball = new Ball(g_sprites.at(2));
		g_remainingBalls.push_back(ball);
	}
}

void	Game::GenerateCanon() {
	g_canon = new Canon(g_sprites.at(3));
	g_canon->SetColor(0, 255, 0);
	g_canon->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
	g_canon->SetOrientation(0, 1);
}

/*
---------------------------------------------------------------------------------
|				Here are all the window related methods							|
---------------------------------------------------------------------------------
*/

void Game::RefreshWindow() {
	g_window->RefreshScreen();
	if (g_currentBall && g_currentBall->isMoving)
		g_window->DrawObject(g_currentBall);
	if (!g_bricks.empty())
		for (int i = 0; i < g_bricksNum; ++i) {
			g_window->DrawObject(g_bricks.at(i));
		}
	g_window->DrawObject(g_canon);
	g_hud->DrawHud(g_window, g_ballNum);
	g_window->w_window->display();
}

void	Game::CloseWindow() {
	g_window->w_window->close();
}

void Game::LimitFps(float fps) {
	g_deltaTime = g_Clock.restart().asSeconds();
	if (g_deltaTime < g_fpsLimit) {
		sleep(seconds(g_fpsLimit - g_deltaTime));
		g_deltaTime += g_fpsLimit - g_deltaTime;
	}
	fps = 1.0f / g_deltaTime;
}

/*
---------------------------------------------------------------------------------
|				Here are all the objects related methods						|
---------------------------------------------------------------------------------
*/

int	Game::NewBall() {
	if (!g_remainingBalls.empty()) {
		g_currentBall = g_remainingBalls.at(g_remainingBalls.size() - 1);
		g_remainingBalls.pop_back();
		g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
		g_canon->SetColor(0, 255, 0);
		return 1;
	}
	return 0;
}

void	Game::SendBall() {
	if (g_currentBall->isMoving == false) {
		g_ballNum--;
		g_currentBall->SetDirection(g_canon->o_angle);
		g_currentBall->isMoving = true;
		g_canon->SetColor(255, 0, 0);
	}
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

/*
---------------------------------------------------------------------------------
|				Here are all the checks related methods							|
---------------------------------------------------------------------------------
*/

void Game::HandleEvents() {
	Event event;
	while (g_window->w_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			CloseWindow();
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			if (!g_currentBall) {
				std::cout << "No more balls available" << std::endl;
				g_isRunning = false;
			}
			else {
				SendBall();
			}
		}
	}
}

void Game::CollCheck() {
	for (int i = 0; i < g_bricks.size(); i++) {
		g_currentBall->CheckCollision(g_bricks.at(i), g_deltaTime);
	}

	for (int i = 0; i < 4; i++) {

		if (g_currentBall->CheckCollision(g_borders[i], g_deltaTime)) {
			if (i == 3) {
				if (!NewBall()) {
					g_isRunning = false;
					g_hud->h_balls.setString(std::to_string(g_ballNum));
				}
			}

		}
	}
}

void Game::EndCheck() {
	if (g_bricks.empty()) {
		std::cout << "Good job ! You won with " << g_ballNum << " Balls Remaining !" << std::endl;
		g_isRunning = false;
	}
	if (g_remainingBalls.empty() && !g_currentBall) {
		std::cout << "Unlucky ! You lost with " << g_bricksNum << " Bricks Remaining !" << std::endl;
		g_isRunning = false;
	}
}

/*
---------------------------------------------------------------------------------
|				Here are all the main methods									|
---------------------------------------------------------------------------------
*/

void Game::Generate() {
	g_map->ParseMap(g_filePath);
	g_map->CheckMap();
	GenerateSprites();
	g_currentBall = new Ball(g_sprites.at(2));
	g_currentBall->SetPos(g_window->GetWidth() / 2, g_window->GetHeight() - 25);
	g_ballNum = g_map->GetBall();
	GenerateTerrain();
	GenerateBorders();
	GenerateCanon();
	GenerateBalls();
}


void Game::GetPath(Vector2i MousePos) {
	std::string res;
	int			x;
	int			y;

	x = MousePos.x;
	y = MousePos.y;
	if (x >= 0 && x <= 266 && y >= 0 && y <= 300) {
		*g_filePath = "rsrc/Level1.txt";
		g_menu = false;
	}
	else if (MousePos.y > 0 && MousePos.y <= 300 and MousePos.x > 266 && MousePos.x <= 532){
		*g_filePath = "rsrc/Level2.txt";
		g_menu = false;
	}
	else if (MousePos.y > 0 && MousePos.y <= 300 and MousePos.x > 532 && MousePos.x <= 800) {
		*g_filePath = "rsrc/Level3.txt";
		g_menu = false;
	}
	else if (MousePos.y > 300 && MousePos.y <= 600 and MousePos.x > 0 && MousePos.x <= 266) {
		*g_filePath = "rsrc/Level4.txt";
		g_menu = false;
	}
	else if (MousePos.y > 300 && MousePos.y <= 600 and MousePos.x > 266 && MousePos.x <= 532) {
		*g_filePath = "rsrc/Level5.txt";
		g_menu = false;
	}
	else if (MousePos.y > 300 && MousePos.y <= 600 and MousePos.x > 532 && MousePos.x <= 800) {
		*g_filePath = "rsrc/Level6.txt";
		g_menu = false;
	}
}

void	Game::DrawMenu() {
	sf::Texture menuTexture;
	sf::Sprite menu;

	if (!menuTexture.loadFromFile("rsrc/menu.png")) {
		std::cout << "Error loading menu.png" << std::endl;
		exit(1);
	}
	menu.setTexture(menuTexture);
	g_window->RefreshScreen();
	g_window->w_window->draw(menu);
	g_window->w_window->display();
}

void Game::Menu() {
	g_menu = true;

	DrawMenu();
	while (g_menu) {
		ChooseLevel();
	}
	g_window->RefreshScreen();
}

void Game::ChooseLevel(){
	Event event;
	while (g_window->w_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			CloseWindow();
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {

			GetPath(Mouse::getPosition(*g_window->w_window));
		}
	}
}


void Game::Start() {
	float	fps = 0;

	while (g_isRunning)
	{
		HandleEvents();
		ClearBricks();
		RefreshWindow();
		EndCheck();
		LimitFps(fps);
		g_canon->FollowMouse(g_window);
		for (int i = 0; i < g_numSim; i++) {
			CollCheck();
			if (g_currentBall->o_shouldMove) {
				g_currentBall->Move(g_deltaTime / g_numSim);
			}
		}
	}
}