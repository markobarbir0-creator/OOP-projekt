#include "Game.h"
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 700), "Connect Four");
    window.setFramerateLimit(60);
   

    Game game;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left)
            {
                Vector2i mis = Mouse::getPosition(window);

                if (game.jeIzbornik())
                    game.obradiKlikIzbornika(mis);
                else if (game.jeIgraGotova())
                    game.obradiKlikEnd(mis);
                else
                    game.handleclick(event.mouseButton.x);
            }

        }
        if (game.getStanje() == Restart)
        {
            game.resetGame();
            game.setStanje(izbornik);
        }

        if (game.getStanje() == Exit)
        {
            window.close();
        }


        game.update();

        window.clear(Color::Black);
        game.draw(window);
        window.display();
    }
    return 0;
}