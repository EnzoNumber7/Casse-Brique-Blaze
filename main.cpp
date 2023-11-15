#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game        game;

    game.Generate();
    game.Start();
    return 0;
}