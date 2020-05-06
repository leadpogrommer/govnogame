#include "Player.h"
#include "MathUtil.h"

Player::Player(Vector2f pos0, float angle0) {
    position = pos0;
    angle = angle0;
    velocity = Vector2f(0, 0);
}

void Player::force(Vector2f dir) {
    velocity = dir;
}

void Player::tick(char tickrate) {
    position.x += velocity.x * 1000/tickrate;
    position.y += velocity.y * 1000/tickrate;
}