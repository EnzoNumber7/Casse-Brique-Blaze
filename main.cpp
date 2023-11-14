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
    //game.Parser();
    cout << game.g_map << endl;

    bool moving = true;

    while (game.g_isRunning)
    {
        game.HandleEvents();
        if (Mouse::getPosition(*game.g_window->w_window).y < game.g_canon->o_posY) {
            game.g_canon->SetOrientation(Mouse::getPosition(*game.g_window->w_window).x, Mouse::getPosition(*game.g_window->w_window).y);
        }
        //game.g_currentBall->o_shape->setOrigin(0.5f, 0.5f);
        //game.g_currentBall->SetPos(0,0);
        //cout << game.g_currentBall->CheckCollision(game.g_borders[1], game.g_deltaTime) << endl;
        //cout << game.g_currentBall->CheckCollision(game.g_bricks.at(0), game.g_deltaTime) << endl;
        
        for (int i = 0; i < game.g_bricks.size(); i++) {
            game.g_currentBall->CheckCollision(game.g_bricks.at(i), game.g_deltaTime);
        }

        for (int i = 0; i < 4; i++) {
            
            game.g_currentBall->CheckCollision(game.g_borders[i], game.g_deltaTime);
            if  (game.g_currentBall->CheckCollision(game.g_borders[i], game.g_deltaTime)) {
                if (i == 3) { 
                    if (game.NewBall()){
						game.g_isRunning = false;
                        game.g_screenBalls.setString(std::to_string(game.g_ballNum));
                    }
                }
               
            }
        }

        if (game.g_currentBall->o_shouldMove) {
            game.g_currentBall->Move(game.g_deltaTime);
        }

		game.ClearBricks();
        game.RefreshWindow();
        game.EndCheck();

        game.g_deltaTime = game.g_Clock.restart().asSeconds();
    }

    return 0;
}