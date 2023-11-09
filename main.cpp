#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameWindow.h"
#include "GameObject.h"

using namespace sf;

int main()
{
    Game        game;
    GameObject  ball('c');
    GameObject  brick('r');
    GameObject  canon('r');

    GameObject rect1('r');
    GameObject rect2('r');

    brick.SetSize(50, 100);
    brick.SetPos(game.g_window->GetWidth()/2, game.g_window->GetHeight());
    brick.SetOrigin(0.5f,0.f);

    rect1.SetSize(50, 50);
    rect1.SetPos(100, 100);
    rect1.SetOrigin(0.5f, 0.5f);
    rect1.SetDirection(0, 1);

    rect2.SetSize(50, 50);
    rect2.SetPos(100,400);
    rect2.SetOrigin(0.5f, 0.5f);

    while (game.g_isRunning)
    {
        game.HandleEvents();
        brick.SetOrientation(Mouse::getPosition(*game.g_window->w_window).x, Mouse::getPosition(*game.g_window->w_window).y);

        rect1.Move(game.g_deltaTime);
        rect1.IsColliding(&rect2);

		game.g_window->w_window->clear();
		game.g_window->DrawObject(&rect1);
		game.g_window->DrawObject(&rect2);
		game.g_window->DrawObject(&ball);
		game.g_window->DrawObject(&brick);
		game.g_window->w_window->display();
        game.g_deltaTime = game.g_Clock.restart().asSeconds();
    }

    return 0;
}