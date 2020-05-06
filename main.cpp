#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "Drawer.h"
#include "Game.h"

using namespace std;

void fuckingError(){
    cout << "Do you suck dicks?"<< endl;
    cout << "Yes you do: " << SDL_GetError() << endl;
    exit(-1);
}

int main() {
    Game game(640, 480);

    game.run();

    return 0;
}