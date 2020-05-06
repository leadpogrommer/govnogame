#pragma once

#include <SDL2/SDL.h>
#include "MathUtil.h"
#include "Drawer.h"


#define ASSERT_NO_NULL(ptr) if(ptr==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(int w, int h);
    void run();
    void stop();
    void setVelocity(Vector2f);

private:
    void init();
    void tick();
    void error(int status = 0);

    bool isRunning;
    Vector2f velocity;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Drawer *drawer;

    Vector2f position;
    float angle;

};
