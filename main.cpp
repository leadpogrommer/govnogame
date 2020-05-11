#include "Game.h"

int main() {
    Game game(800, 600, sf::IpAddress(), 0);

    game.init();
    game.run();

    return 0;
}