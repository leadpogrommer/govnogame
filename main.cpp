#include "Game.h"
#include "Server.h"
#include <thread>

int main(int argc, char** argv) {

    Game game(800, 600, sf::IpAddress(argv[0]), 1488);


    game.init();
    game.run();

    return 0;
}