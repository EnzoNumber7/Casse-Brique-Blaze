#include <iostream>
#include <SFML/Graphics.hpp>
#include "Base.h"
#include "Game.h"

int main()
{
    Game        game;

    game.Menu();
    game.Generate();
    game.Start();
    return 0;
}