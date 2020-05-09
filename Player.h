#pragma once
#include "MathUtil.h"

class Player {
public:
    Player(Vector2f pos0, float angle0);
    void tick(float tickrate);
    void force(Vector2f dir);

    Vector2f position;
    Vector2f velocity;
    float angle;
    float angularVelocity = 0;
};