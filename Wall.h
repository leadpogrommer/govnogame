#pragma once

#include "MathUtil.h"
#include <SFML/Graphics.hpp>

class Wall {
public:
    Wall(Segment s, sf::Color c): segment(s), color(c) {}

    Segment segment;
    sf::Color color;

};


