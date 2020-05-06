#pragma once

#include <SDL2/SDL.h>
#include <cmath>

#include "MathUtil.h"


class Drawer {
public:
    explicit Drawer(SDL_Window* w);
    void render(Vector2f, float);

    const int mapSize = 2;
    Segment map[2] = {Segment(-3, -3, 0, 6), Segment(0, 8, 3, 2)};


private:
    static float getDistance(Segment s, Vector2f pos, float angle);

    SDL_Renderer* r;
    SDL_Window* window;
    int w{};
    int h{};

};




