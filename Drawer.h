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

    const static int mapSize = 3;
    Wall map[mapSize] = {Wall(Segment(-2, 5, 2, 2), "loh.jpeg"), Wall(Segment(-2, 3, 4, 3), "2.png"), Wall(Segment(0, 2, 2, 4), "1.png")};
//    Wall map[mapSize] = {Wall(Segment(-2, 5, 2, 2), "1.png")};
//    Wall map[mapSize] = {Wall(Segment(1, 1, 1, 4), "r.png"), Wall(Segment(1, 4, 4, 6), "g.png"), Wall(Segment(4, 6, 1, 1), "b.png"), Wall(Segment(0, 2, 4, 2), "1.png")};


private:
    sf::RenderWindow* window;
    int w;
    int h;
    static sf::VertexArray generateRect(int x, int y, int w, int h, sf::Color color);

    float *zbuffer;

};




