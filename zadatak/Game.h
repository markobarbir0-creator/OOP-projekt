#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <string>
using namespace sf;
using namespace std;

enum StanjeIgre { izbornik, Menu, DvaIgraca, JedanIgrac, Restart, Exit };

struct Player {
    int id;
    string name;
};

class Game {
private:
    Board board;
    Player p1, p2;
    int currentplayer;
    int stupac, red;
    int animstupac, animred, animigrac;
    bool igragotova, pada, prikazprvog;
    float animY, brzina;
    StanjeIgre stanjeIgre;
    int pobjednik;
    Clock prvi;
    Font font;
    RectangleShape gumbDvaIgraca, gumbRacunalo, gumbRestart, gumbExit;
    Text naslov, tekstDvaIgraca, tekstRacunalo, tekstRestart, tekstExit, tekstPrvi, tekstPobjede;

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
    bool mozePobjedit(int igrac, int stupac);
    int odaberiNajboljiStupacAI();
    void draw(RenderWindow& w);
};
