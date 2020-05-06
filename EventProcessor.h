#pragma once


class Game;
#include "Game.h"


class EventProcessor {
public:
    explicit EventProcessor(Game *g);
    void process();

private:
    Game* game;
    void processKey(SDL_Keycode, bool);
    Vector2f velocity;
    float aw = 0;

};