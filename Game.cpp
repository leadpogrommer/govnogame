#include "Game.h"
#include <iostream>
#include <cmath>


Game::Game(int w, int h, char tickrate): character(Player(Vector2f(0, 0), M_PI/2)) {
    this->width = w;
    this->height = h;

}

void Game::error(int status) {
    std::cout << "ERROR!" << std::endl;
    std::cout << "Code = " << status << std::endl;

    throw std::exception();
}

void Game::stop() {
    isRunning = false;
}

void Game::run() {
    while (window->isOpen()) {
        tick();

        sf::sleep(sf::milliseconds(1000/tickrate));
    }
}

void Game::init() {
    window = new sf::RenderWindow(sf::VideoMode(width, height), "DICKS", sf::Style::Titlebar | sf::Style::Close);
    window->setKeyRepeatEnabled(false);

    drawer = new Drawer(window);
    eventer = new EventProcessor(this);
}

void Game::setCharacter(Player c) {
    this->character = c;
}

void Game::tick() {
    eventer->process();

    character.tick(tickrate);

    drawer->render(character.position, character.angle);
//    drawer->renderDebug(character.position, character.angle);
}

Game::~Game() {
    delete window;
    delete drawer;
    delete eventer;
}