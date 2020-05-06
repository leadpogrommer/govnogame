#include "Player.h"
#include "MathUtil.h"

Player::Player(Vector2f pos0, float angle0): velocity(0, 0), position(pos0) {
    angle = angle0;
}

void Player::force(Vector2f dir) {
    velocity = dir;
}

void Player::tick(char tickrate) {
    float t = 1000/tickrate;

    position.x += (velocity.y * cos(angle) + velocity.x*cos(angle - M_PI / 2))*t;
    position.y += (velocity.y * sin(angle) + velocity.x*sin(angle - M_PI / 2))*t;

    angle += angularVelocity * t;
    PREPARE_ANGLE(angle);
}