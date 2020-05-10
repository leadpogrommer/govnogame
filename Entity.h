#pragma once

#include <SFML/Graphics.hpp>
#include "MathUtil.h"

class Entity {
public:
    Vector2f pos;
    float z;
    sf::Texture texture;

    Entity(Vector2f p, float _z, const char* textureFilename): pos(p), z(_z){
        texture.loadFromFile(textureFilename);
    }
};

