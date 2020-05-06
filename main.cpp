#include "Game.h"
#include "Player.h"

int main() {
    Game game(640, 480, 32);

    Player character(Vector2f(0, 0), 0);
    game.setCharacter(character);

    game.run();

    return 0;
}