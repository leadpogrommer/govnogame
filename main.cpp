#include "Game.h"

int main() {
    Game game(1920*2 - 50, 1080*2 - 50);

    game.init();
    game.run();

    return 0;
}