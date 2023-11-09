#pragma once
class GameWindow;
class GameObject;
#include <SFML/System/Clock.hpp>

class Game
{
public:

	GameWindow*					g_window;
	bool						g_isRunning;
	sf::Clock					g_Clock;
	float						g_deltaTime;
	GameObject*					g_currentBall;
	std::vector<GameObject*>	g_remainingBalls;
	std::vector<GameObject*>	g_bricks;
	int							g_ballNum;

	Game();

	void						CloseWindow();
	void						HandleEvents();
	int							NewBall();
	void						DestroyBall();
	void						RefreshWindow();
};

