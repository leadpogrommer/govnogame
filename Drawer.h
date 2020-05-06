#pragma once


#include <cmath>

#include <string>
#include "MathUtil.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>

class Drawer {
public:
    explicit Drawer(sf::RenderWindow* w);
    ~Drawer();
    void render(Vector2f, float);
    void renderDebug(Vector2f, float);

    const static int mapSize = 2;
    Wall map[mapSize] = {Wall(Segment(-2, 5, 2, 2), sf::Color::Red), Wall(Segment(-2, 3, 4, 3), sf::Color::Green)};


private:
//    static float getDistance(Segment s, Vector2f pos, float angle);

//    SDL_Texture *drawText(std::string msg, SDL_Color &color, int tox, int toy);

    sf::RenderWindow* window;
    int w;
    int h;
    sf::VertexArray generateRect(int x, int y, int w, int h, sf::Color color);
    //TODO: free zbuffer
    float *zbuffer;

};




