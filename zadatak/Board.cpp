#include "Board.h"

const float CELL_WIDTH = 800.0f / 7;
const float CELL_HEIGHT = 700.0f / 6;
const float PADDING = 10.f;

Board::Board() {
    grid.resize(rows, vector<int>(columns, 0));
    Boardshape.setSize(Vector2f(800.f, 700.f));
    Boardshape.setFillColor(Color::Blue);
}

void Board::draw(RenderWindow& window) {
    window.draw(Boardshape);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            CircleShape krug(45.f);
            krug.setPosition(j * CELL_WIDTH + PADDING, i * CELL_HEIGHT + PADDING);

            if (grid[i][j] == 0) krug.setFillColor(Color::White);
            else if (grid[i][j] == 1) krug.setFillColor(Color::Yellow);
            else krug.setFillColor(Color::Red);

            window.draw(krug);
        }
    }
}

bool Board::jelipun(int stupac) {
    return grid[0][stupac] != 0;
}

bool Board::pronadired(int stupac, int& red) {
    for (int i = rows - 1; i >= 0; i--) {
        if (grid[i][stupac] == 0) {
            red = i;
            return true;
        }
    }
    return false;
}

bool Board::provjerapobjede(int igrac, int stupac, int red) {
    int brojac = 0;

    // Vertikalno
    for (int i = 0; i < rows; i++) {
        brojac = (grid[i][stupac] == igrac) ? brojac + 1 : 0;
        if (brojac == 4) return true;
    }

    // Horizontalno
    brojac = 0;
    for (int j = 0; j < columns; j++) {
        brojac = (grid[red][j] == igrac) ? brojac + 1 : 0;
        if (brojac == 4) return true;
    }

    // Dijagonale 
    for (int i = 0; i <= rows - 4; i++)
    for (int j = 0; j <= columns - 4; j++)
        if (grid[i][j] == igrac && grid[i + 1][j + 1] == igrac &&
            grid[i + 2][j + 2] == igrac && grid[i + 3][j + 3] == igrac)
            return true;

    // Dijagonale /
    for (int i = 0; i <= rows - 4; i++)
        for (int j = 3; j < columns; j++)
            if (grid[i][j] == igrac && grid[i + 1][j - 1] == igrac &&
                grid[i + 2][j - 2] == igrac && grid[i + 3][j - 3] == igrac)
                return true;

    return false;
}

void Board::postavizeton(int red, int stupac, int igrac) {
    grid[red][stupac] = igrac;
}

void Board::reset() {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            grid[i][j] = 0;
}
