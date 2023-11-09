#pragma once
class GameWindow;
class GameObject;
#include <SFML/System/Clock.hpp>

class Game
{
public:

	sf::Clock					g_Clock;
	std::vector<GameObject*>	g_remainingBalls;
	std::vector<GameObject*>	g_bricks;
	GameObject*					g_borders[4];
	GameObject*					g_canon;
	GameWindow*					g_window;
	GameObject*					g_currentBall;
	bool						g_isRunning;
	float						g_deltaTime;
	int							g_bricksNum;
	int							g_ballNum;

	Game();

	void						CloseWindow();
	void						HandleEvents();
	int							NewBall();
	void						DestroyBall();
	void						RefreshWindow();
	void						GenerateTerrain();
	void						GenerateCanon();
	void						GenerateBorders();

private:
	void						SetBorder(GameObject* border, char id);
};

