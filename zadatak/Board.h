#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Board {
private:
    vector<vector<int>> grid;
    RectangleShape Boardshape;

public:
    const int rows = 6;
    const int columns = 7;

    Board();

    void draw(RenderWindow& window);
    bool jelipun(int stupac);
    bool pronadired(int stupac, int& red);
    bool provjerapobjede(int igrac, int stupac, int red);
    void postavizeton(int red, int stupac, int igrac);
    void reset();
};

#endif
