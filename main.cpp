#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "GameObject.h"

using namespace sf;

int main()
{
    GameWindow window;
    GameObject ball('c');
    GameObject brick('r');

    brick.setSize(500, 200);
    brick.setPos(500.f, 200.f);

    ball.setSize(100, 100);
    

    while (window.w_window->isOpen())
    {
        Event event;
        while (window.w_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.w_window->close();
        }

        window.w_window->clear();
        window.DrawObject(&ball);
        window.DrawObject(&brick);
        window.w_window->display();
    }

    return 0;
}