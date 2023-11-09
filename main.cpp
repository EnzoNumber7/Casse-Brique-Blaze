#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameWindow.h"
#include "GameObject.h"

using namespace sf;
using namespace std;

int main()
{
    Game        game;
    GameObject  brick('r');
    GameObject  canon('r');

    GameObject rect1('r');
    GameObject rect2('r');
    GameObject rect3('r');
    GameObject rect4('r');
    GameObject rect5('r');

    brick.SetSize(50, 100);
    brick.SetPos(game.g_window->GetWidth()/2, game.g_window->GetHeight());
    brick.SetOrigin(0.5f,0.f);

    rect1.SetSize(50, 50);
    rect1.SetPos(350, 100);
    rect1.SetOrigin(0.5f, 0.5f);
    rect1.SetDirection(0.5, 1);

    rect2.SetSize(5000, 50);
    rect2.SetPos(100,400);
    rect2.SetOrigin(0.5f, 0.5f);

    while (game.g_isRunning)
    {
        game.HandleEvents();
        brick.SetOrientation(Mouse::getPosition(*game.g_window->w_window).x, Mouse::getPosition(*game.g_window->w_window).y);

        if (rect1.IsColliding(&rect2) == 'n') {
            rect1.Move(game.g_deltaTime);
        }
        else {
            rect1.Rebound(rect1.IsColliding(&rect2), game.g_deltaTime);
        }
        
		game.g_currentBall->Move(game.g_deltaTime);
		game.g_window->w_window->clear();
		game.g_window->DrawObject(&rect1);
		game.g_window->DrawObject(&rect2);

		game.g_window->DrawObject(&brick);
		game.g_window->DrawObject(game.g_currentBall);
		game.g_window->w_window->display();
        game.g_deltaTime = game.g_Clock.restart().asSeconds();
    }

    return 0;
}