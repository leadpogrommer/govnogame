#include "Game.h"
#include "Server.h"
#include <thread>

int main() {
    Game game(800, 600);

    Server server;

    game.init();
    game.run();

    return 0;
}