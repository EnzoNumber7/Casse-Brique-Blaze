#pragma once
class GameWindow;
class Hud;
class Map;
class Canon;
class Ball;
class Brick;
class Border;

#include <SFML/System/Clock.hpp>

class Game
{
private:

	// Main Attributes

	GameWindow* g_window;
	Hud* g_hud;

	Map* g_map;

	// Time Attributes

	bool						g_isRunning;
	sf::Clock					g_Clock;
	float						g_deltaTime;
	float						g_fpsLimit;

	// Game Objects

	int							g_bricksNum;
	std::vector<Brick*>			g_bricks;

	int							g_ballNum;
	std::vector<Ball*>			g_remainingBalls;
	Ball*						g_currentBall;

	Border*						g_borders[4];

	Canon*						g_canon;


public:

	Game();

	// Called in main

	void						Start();
	void						Generate();

private:
	
	// Generation

	void						GenerateTerrain();
	void						SetBorder(Border* border, char id);
	void						GenerateBorders();
	void						GenerateCanon();
	void						GenerateBalls();

	// Window related

	void						RefreshWindow();
	void						CloseWindow();
	void						LimitFps(float fps);

	// Obj related

	int							NewBall();
	void						SendBall();
	void						DestroyBall();

	void						ClearBricks();

	// Checks Related
	
	void						HandleEvents();
	void						CollCheck();
	void						EndCheck();
};

