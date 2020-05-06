#pragma once

class EventProcessor;
#include <SDL2/SDL.h>
#include <vector>
#include "MathUtil.h"
#include "Drawer.h"
#include "EventProcessor.h"
#include "Player.h"


#define ASSERT_NO_NULL(ptr) if(ptr==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(int w, int h, char tickrate);
    ~Game();
    void run();
    void stop();
    void setCharacter(Player character);

private:
    friend class EventProcessor;
    void init();
    void tick();
    void error(int status = 0);

    Player character;
    char tickrate;
    bool isRunning;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Drawer *drawer;
    EventProcessor *eventer;
};
