#include "Game.h"
#include "Player.h"

int main() {
    Game game(640, 480, 32);

    game.init();
    game.run();

    return 0;
}