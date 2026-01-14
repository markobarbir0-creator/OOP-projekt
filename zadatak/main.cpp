#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 700), "Connect Four");
    Game game;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (game.getStanje() == izbornik || game.getStanje() == Menu) {
                    game.obradiKlikIzbornika(mousePos);
                }
                else if (game.jeIgraGotova()) {
                    game.obradiKlikEnd(mousePos);
                    if (game.getStanje() == Restart) {
                        game.resetGame();
                    }
                    else if (game.getStanje() == Exit) window.close();
                }
                else {
                    game.handleclick(mousePos.x);
                }
            }
        }
        game.update();
        window.clear(Color::Black);
        game.draw(window);
        window.display();
    }
    return 0;
}
