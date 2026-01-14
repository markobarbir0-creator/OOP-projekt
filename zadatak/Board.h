#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Board {
public:
    int rows = 6;
    int columns = 7;
    vector<vector<int>> grid;
    RectangleShape Boardshape;

    Board();
    void draw(RenderWindow& window);
    bool jelipun(int stupac);
    bool pronadired(int stupac, int& red);
    bool provjerapobjede(int igrac, int stupac, int red);
    void postavizeton(int red, int stupac, int igrac);
    void uklonizeton(int red, int stupac);
    void reset();
};
