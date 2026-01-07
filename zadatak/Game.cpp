#include "Game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const float CELL_WIDTH = 800.0f / 7;
const float CELL_HEIGHT = 700.0f / 6;
const float PADDING = 10.f;

Game::Game() {
    srand(time(nullptr));
    stanjeIgre = izbornik;
    p1.id = 1;
    p2.id = 2;
    currentplayer = rand() % 2 + 1;

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    naslov.setFont(font);
    naslov.setString("CONNECT 4");
    naslov.setCharacterSize(60);
    naslov.setPosition(200, 100);

    gumbDvaIgraca.setSize(Vector2f(450, 80));
    gumbDvaIgraca.setPosition(150, 250);
    gumbDvaIgraca.setFillColor(Color::Green);

    gumbRacunalo.setSize(Vector2f(450, 80));
    gumbRacunalo.setPosition(150, 360);
    gumbRacunalo.setFillColor(Color::Red);

    gumbExit.setSize(Vector2f(450, 80));
    gumbExit.setPosition(150, 250);
    gumbExit.setFillColor(Color::Green);

    gumbRestart.setSize(Vector2f(450, 80));
    gumbRestart.setPosition(150, 360);
    gumbRestart.setFillColor(Color::Red);

    tekstDvaIgraca.setFont(font);
    tekstDvaIgraca.setString("PLAYER VS PLAYER");
    tekstDvaIgraca.setCharacterSize(40);
    tekstDvaIgraca.setPosition(180, 265);

    tekstRacunalo.setFont(font);
    tekstRacunalo.setString("PLAYER VS BOT");
    tekstRacunalo.setCharacterSize(40);
    tekstRacunalo.setPosition(180, 375);

    tekstRestart.setFont(font);
    tekstRestart.setString("RESTART");
    tekstRestart.setCharacterSize(40);
    tekstRestart.setPosition(180, 375);

    tekstExit.setFont(font);
    tekstExit.setString("EXIT");
    tekstExit.setCharacterSize(40);
    tekstExit.setPosition(180, 265);

    tekstPobjede.setFont(font);
    tekstPobjede.setCharacterSize(50);
    tekstPobjede.setPosition(200, 100);

    tekstPrvi.setFont(font);
    tekstPrvi.setCharacterSize(60);
    tekstPrvi.setPosition(180, 350);

    pada = false;
    animY = 0;
    brzina = CELL_HEIGHT / (0.5f * 60);
    igragotova = false;
    prikazprvog = false;
}

bool Game::jeIzbornik() { return stanjeIgre == izbornik; }
bool Game::jeMenu() { return stanjeIgre == Menu; }
bool Game::jeIgraGotova() { return igragotova; }
StanjeIgre Game::getStanje() { return stanjeIgre; }
void Game::setStanje(StanjeIgre s) { stanjeIgre = s; }

Board& Game::getboard() { return board; }

void Game::obradiKlikEnd(Vector2i mis) {
    if (gumbRestart.getGlobalBounds().contains(mis.x, mis.y))
        stanjeIgre = Restart;
    else if (gumbExit.getGlobalBounds().contains(mis.x, mis.y))
        stanjeIgre = Exit;
}

void Game::obradiKlikIzbornika(Vector2i mis) {
    if (gumbDvaIgraca.getGlobalBounds().contains(mis.x, mis.y)) {
        stanjeIgre = DvaIgraca;
        cout << "Unesi ime igraca 1: ";
        cin >> p1.name;
        cout << "Unesi ime igraca 2: ";
        cin >> p2.name;
        prikazprvog = true;
        tekstPrvi.setString("Prvi igra: " + ((currentplayer == 1) ? p1.name : p2.name));
        prvi.restart();
    }
    else if (gumbRacunalo.getGlobalBounds().contains(mis.x, mis.y)) {
        stanjeIgre = JedanIgrac;
        cout << "Unesi ime igraca: ";
        cin >> p1.name;
        p2.name = "BOT";
        prikazprvog = true;
        tekstPrvi.setString("Prvi igra: " + ((currentplayer == 1) ? p1.name : p2.name));
        prvi.restart();
    }
}

void Game::handleclick(int x) {
    if ((stanjeIgre == izbornik || stanjeIgre == Menu) || igragotova || pada) return;

    stupac = x / CELL_WIDTH;
    if (stupac >= 0 && stupac < 7 && !board.jelipun(stupac)) {
        board.pronadired(stupac, red);
        pada = true;
        animstupac = stupac;
        animred = red;
        animigrac = currentplayer;
        animY = 0;
    }
}

void Game::update() {
    if (prikazprvog) {
        if (prvi.getElapsedTime().asSeconds() > 5.0f) prikazprvog = false;
        else return;
    }

    if (stanjeIgre == JedanIgrac && currentplayer == 2 && !pada && !igragotova) {
        int s;
        do { s = rand() % 7; } while (board.jelipun(s));
        handleclick(s * CELL_WIDTH);
    }

    if (!pada) return;

    float ciljaniY = animred * CELL_HEIGHT + PADDING;
    if (animY < ciljaniY) animY += brzina;
    else {
        board.postavizeton(animred, animstupac, animigrac);
        pada = false;

        if (board.provjerapobjede(animigrac, animstupac, animred)) {
            igragotova = true;
            pobjednik = animigrac;
            tekstPobjede.setString((pobjednik == 1 ? p1.name : p2.name) + " JE POBIJEDIO");
            tekstPobjede.setFillColor(pobjednik == 1 ? Color::Yellow : Color::Red);
        }
        else currentplayer = (currentplayer == 1 ? 2 : 1);
    }
}

void Game::resetGame() {
    board.reset();
    igragotova = false;
    pada = false;
    prikazprvog = false;
    currentplayer = rand() % 2 + 1;
}

void Game::draw(RenderWindow& w) {
    if (stanjeIgre == izbornik) {
        w.draw(naslov);
        w.draw(gumbDvaIgraca);
        w.draw(gumbRacunalo);
        w.draw(tekstDvaIgraca);
        w.draw(tekstRacunalo);
        return;
    }

    if (prikazprvog) {
        w.draw(tekstPrvi);
        return;
    }

    if (!igragotova) board.draw(w);
    else {
        w.draw(tekstPobjede);
        w.draw(gumbRestart);
        w.draw(gumbExit);
        w.draw(tekstRestart);
        w.draw(tekstExit);
    }

    if (pada) {
        CircleShape c(45.f);
        c.setPosition(animstupac * CELL_WIDTH + PADDING, animY);
        c.setFillColor(animigrac == 1 ? Color::Yellow : Color::Red);
        w.draw(c);
    }
}
