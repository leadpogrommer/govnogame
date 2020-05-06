#include "Game.h"
#include <iostream>
#include <cmath>


Game::Game(int w, int h): velocity(0, 0), width(w), height(h), position(0, 0), angle(M_PI/2), angularVelocity(0) {}

void Game::error(int status) {
    std::cout << "ERROR!" << std::endl;
    std::cout << "Code = " << status << std::endl;
    std::cout << "SDL Error = " << SDL_GetError() << std::endl;

    throw std::exception();
}

void Game::setVelocity(Vector2f v) {
    this->velocity = v;
}

void Game::stop() {
    this->isRunning = false;
}

void Game::run() {
    isRunning = true;
    try {
        init();
    }catch (std::exception &e){
        return;
    }

    while (isRunning){
        tick();
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        error();
    }

    if (TTF_Init() != 0){
        error();
    }



    window = SDL_CreateWindow("Dicks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    ASSERT_NO_NULL(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ASSERT_NO_NULL(renderer);

    drawer = new Drawer(window);
    eventer = new EventProcessor(this);

}

void Game::tick() {
    eventer->process();

    position.x += velocity.y*cos(angle) + velocity.x*cos(angle + M_PI/2);
    position.y += velocity.y*sin(angle) + velocity.x*sin(angle + M_PI/2);




    angle += angularVelocity;

    drawer->render(position, angle);
}

Game::~Game() {
    free(drawer);
    free(eventer);
}



