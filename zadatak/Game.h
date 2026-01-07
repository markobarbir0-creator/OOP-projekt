#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

enum StanjeIgre {
    izbornik,
    DvaIgraca,
    JedanIgrac,
    Menu,
    Exit,
    Restart
};

class Game {
private:
    Board board;
    Player p1, p2;
    int currentplayer;
    int stupac, red;
    bool pada;
    int animstupac, animred, animigrac;
    float animY;
    float brzina;
    bool igragotova;
    int pobjednik;
    bool prikazprvog;

    StanjeIgre stanjeIgre;

    RectangleShape gumbDvaIgraca;
    RectangleShape gumbRacunalo;
    RectangleShape gumbExit;
    RectangleShape gumbRestart;
    Font font;
    Text naslov, tekstDvaIgraca, tekstRacunalo, tekstPobjede, tekstPrvi;
    Clock prvi;
    Text tekstRestart, tekstExit;

public:
    Game();

    bool jeIzbornik();
    bool jeMenu();
    bool jeIgraGotova();
    StanjeIgre getStanje();
    void setStanje(StanjeIgre s);

    Board& getboard();
    void obradiKlikEnd(Vector2i mis);
    void obradiKlikIzbornika(Vector2i mis);
    void handleclick(int x);
    void update();
    void resetGame();
    void draw(RenderWindow& w);
};

#endif

