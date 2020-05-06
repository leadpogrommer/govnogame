#include "Game.h"
#include <iostream>
#include <cmath>


Game::Game(int w, int h, char tickrate) {
    this.width = w;
    this.height = h;
}

void Game::error(int status) {
    std::cout << "ERROR!" << std::endl;
    std::cout << "Code = " << status << std::endl;
    std::cout << "SDL Error = " << SDL_GetError() << std::endl;

    throw std::exception();
}

void Game::stop() {
    isRunning = false;
}

void Game::run() {
    isRunning = true;

    try init();
    catch (std::exception &e) return;

    while (isRunning) {
        tick();

        SDL_Delay(1000/tickrate);
    }
}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) error();

    if (TTF_Init() != 0) error();

    window = SDL_CreateWindow("Dicks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    ASSERT_NO_NULL(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ASSERT_NO_NULL(renderer);

    drawer = new Drawer(window);
    eventer = new EventProcessor(this);
}

void Game::setCharacter(Player character) {
    this.character = character;
}

void Game::tick() {
    eventer->process();

    character.tick(tickrate);

    drawer->render(character.position, character.angle);
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete drawer;
    delete eventer;
}