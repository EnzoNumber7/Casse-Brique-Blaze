#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "GameObject.h"

using namespace sf;

int main()
{
    GameWindow  window;
    Clock       oClock;
    float       deltaTime;
    GameObject  ball('c');
    GameObject  brick('r');
    GameObject  canon('r');

    GameObject rect1('r');
    GameObject rect2('r');

	deltaTime = 0.f;

    brick.SetSize(50, 100);
    brick.SetPos(window.GetWidth()/2, window.GetHeight());
    brick.SetOrigin(0.5f,0.f);

    rect1.SetSize(50, 50);
    rect1.SetDirection(0, 1);

    rect2.SetSize(50, 50);
    rect2.SetPos(0, 500);



    

    while (window.w_window->isOpen())
    {
        Event event;
        while (window.w_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.w_window->close();
        }
        brick.SetOrientation(Mouse::getPosition(*window.w_window).x, Mouse::getPosition(*window.w_window).y);

        rect1.Move(deltaTime);
        rect1.IsColliding(&rect2);

        window.w_window->clear();
        window.DrawObject(&rect1);
        window.DrawObject(&rect2);
        window.DrawObject(&ball);
        window.DrawObject(&brick);
        window.w_window->display();
        deltaTime = oClock.restart().asSeconds();
    }

    return 0;
}