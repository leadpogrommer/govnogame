#pragma once

#include "MathUtil.h"
#include <SFML/Graphics.hpp>

class Wall {
public:
    Wall(Segment s, const char *textureFileName): segment(s) {
        texture.loadFromFile(textureFileName);
        sprite.setTexture(texture);
    }

    Segment segment;
    sf::Texture texture;
    sf::Sprite sprite;

};


