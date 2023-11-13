#pragma once
class GameWindow;
class GameObject;
class Canon;
class Ball;
class Brick;
class Border;

#include <SFML/System/Clock.hpp>

class Game
{
public:

	sf::Clock					g_Clock;
	std::vector<Ball*>			g_remainingBalls;
	std::vector<Brick*>			g_bricks;
	Border*						g_borders[4];
	Canon*						g_canon;
	GameWindow*					g_window;
	Ball*						g_currentBall;
	bool						g_isRunning;
	float						g_deltaTime;
	int							g_bricksNum;
	int							g_ballNum;

	Game();

	void						CloseWindow();
	void						HandleEvents();
	int							NewBall();
	void						SendBall();
	void						DestroyBall();
	void						ClearBricks();
	void						RefreshWindow();
	void						GenerateBalls();
	void						GenerateTerrain();
	void						GenerateCanon();
	void						GenerateBorders();

private:
	void						SetBorder(Border* border, char id);
};

