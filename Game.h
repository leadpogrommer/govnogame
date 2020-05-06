#pragma once

class EventProcessor;
#include <SDL2/SDL.h>
#include "MathUtil.h"
#include "Drawer.h"
#include "EventProcessor.h"


#define ASSERT_NO_NULL(ptr) if(ptr==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(int w, int h);
    ~Game();
    void run();
    void stop();
    void setVelocity(Vector2f);

private:
    friend class EventProcessor;
    void init();
    void tick();
    void error(int status = 0);

    bool isRunning;
    Vector2f velocity;
    float angularVelocity;
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Drawer *drawer;
    EventProcessor *eventer;

    Vector2f position;
    float angle;

};
