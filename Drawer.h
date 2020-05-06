#pragma once

#include <SDL2/SDL.h>
#include <cmath>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "MathUtil.h"


class Drawer {
public:
    explicit Drawer(SDL_Window* w);
    ~Drawer();
    void render(Vector2f, float);

    const int mapSize = 2;
    Segment map[2] = {Segment(-3, -3, 0, 6), Segment(0, 8, 3, 2)};


private:
    static float getDistance(Segment s, Vector2f pos, float angle);
    void renderDebug();
    SDL_Texture *drawText(std::string msg, SDL_Color color);

    SDL_Renderer* r;
    SDL_Window* window;
    int w;
    int h;

    TTF_Font *font;
    //TODO: free zbuffer
    float *zbuffer;

};




