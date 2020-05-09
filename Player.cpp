#include "Player.h"
#include "MathUtil.h"

Player::Player(Vector2f pos0, float angle0): velocity(0, 0), position(pos0) {
    angle = angle0;
}

void Player::force(Vector2f dir) {
    velocity = dir;
}

void Player::tick(float tickrate) {
    float t = 1000.0f/tickrate;

    position.x += (velocity.y * cosf(angle) + velocity.x*cosf(angle - M_PI / 2))*t;
    position.y += (velocity.y * sinf(angle) + velocity.x*sinf(angle - M_PI / 2))*t;

    angle += angularVelocity * t;
    PREPARE_ANGLE(angle);
}