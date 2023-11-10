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

    brick.SetSize(50, 100);
    brick.SetPos(game.g_window->GetWidth() / 2, game.g_window->GetHeight());
    game.GenerateTerrain();
    game.GenerateCanon();
    game.GenerateBorders();
    while (game.g_isRunning)
    {

        game.HandleEvents();
        if (Mouse::getPosition(*game.g_window->w_window).y < game.g_window->w_height)
            game.g_canon->SetOrientation(Mouse::getPosition(*game.g_window->w_window).x, Mouse::getPosition(*game.g_window->w_window).y);

        for (int i = 0; i < game.g_bricks.size(); i++) {
            if (game.g_currentBall->IsColliding(game.g_bricks.at(i)) != 'n') {
                game.g_currentBall->Rebound(game.g_currentBall->IsColliding(game.g_bricks.at(i)), game.g_deltaTime);
            }
        }

        for (int i = 0; i < 4; i++) {
            if (game.g_currentBall->IsColliding(game.g_borders[i]) == 'n' and game.g_currentBall->o_directionX != 0 and game.g_currentBall ->o_directionY != 0) {
                game.g_currentBall->Move(game.g_deltaTime);
            }
            else if (game.g_currentBall->IsColliding(game.g_borders[i]) != 'n'){
                if (i == 3) { 
                    if (game.NewBall()){
						game.g_isRunning = false;
                    }
                }
                else game.g_currentBall->Rebound(game.g_currentBall->IsColliding(game.g_borders[i]), game.g_deltaTime);
            }
        }

        game.RefreshWindow();
		game.g_window->w_window->clear();


		game.g_window->DrawObject(&brick);
		game.g_window->DrawObject(game.g_currentBall);
        game.g_deltaTime = game.g_Clock.restart().asSeconds();
    }

    return 0;
}