#include "Game.h"
#include <iostream>



Game::Game(int w, int h): velocity(0, 0), width(w), height(h), position(0, 0), angle(M_PI/2) {}

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
    try {
        init();
    }catch (std::exception &e){
        return;
    }

    while (isRunning){
        tick();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        error();
    }

    window = SDL_CreateWindow("Dicks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    ASSERT_NO_NULL(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ASSERT_NO_NULL(renderer);

    drawer = new Drawer(window);

}

void Game::tick() {
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT: stop();
                break;
        }
    }

    drawer->render(position, angle);

}



