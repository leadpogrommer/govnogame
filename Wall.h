#pragma once

#include "MathUtil.h"
#include <SFML/Graphics.hpp>

class Wall {
public:
    Wall(Segment s, char* tname): segment(s) {
        texture.loadFromFile(tname);
        sprite.setTexture(texture);
    }

    Segment segment;
    sf::Texture texture;
    sf::Sprite sprite;

};


