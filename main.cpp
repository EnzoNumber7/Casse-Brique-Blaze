#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Canon.h"
#include "Brick.h"
#include "Border.h"
#include "Game.h"
#include "GameWindow.h"
#include "GameObject.h"

using namespace sf;
using namespace std;

int main()
{
    Game        game;

    game.GenerateTerrain();
    game.GenerateCanon();
    game.GenerateBorders();
    game.GenerateBalls();


    while (game.g_isRunning)
    {
        game.HandleEvents();
        if (Mouse::getPosition(*game.g_window->w_window).y < game.g_window->w_height) {
            game.g_canon->SetOrientation(Mouse::getPosition(*game.g_window->w_window).x, Mouse::getPosition(*game.g_window->w_window).y);
        }

        //game.g_currentBall->SetPos(220,210);

        //cout << game.g_currentBall->CheckCollision(game.g_bricks.at(0), game.g_deltaTime) << endl;
        
        for (int i = 0; i < game.g_bricks.size(); i++) {
            game.g_currentBall->CheckCollision(game.g_bricks.at(i), game.g_deltaTime);
        }

        for (int i = 0; i < 4; i++) {
            if (not game.g_currentBall->CheckCollision(game.g_borders[i], game.g_deltaTime) and game.g_currentBall->o_directionX != 0 and game.g_currentBall->o_directionY != 0) {
                game.g_currentBall->Move(game.g_deltaTime);
            }
            else if  (game.g_currentBall->CheckCollision(game.g_borders[i], game.g_deltaTime)) {
                if (i == 3) { 
                    if (game.NewBall()){
						game.g_isRunning = false;
                    }
                }
               
            }
        }

        game.RefreshWindow();

        game.g_deltaTime = game.g_Clock.restart().asSeconds();
    }

    return 0;
}