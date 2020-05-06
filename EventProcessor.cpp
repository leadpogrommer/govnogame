#include "EventProcessor.h"
#include <iostream>
#define SPEED 0.3

EventProcessor::EventProcessor(Game *g): game(g) {}

void EventProcessor::process() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if ( event.key.repeat)continue;
        switch (event.type){
            case SDL_QUIT:
                game->stop();
                break;

            case SDL_KEYDOWN:
                processKey(event.key.keysym.sym, false);
                break;
            case SDL_KEYUP:
                processKey(event.key.keysym.sym, true);
                break;
        }
    }
}

void EventProcessor::processKey(SDL_Keycode k, bool isUp) {

    Vector2f toAdd(0, 0);
    float toAddA = 0.0;

    switch (k){
        case SDLK_a: toAdd.x -= SPEED; break;
        case SDLK_d: toAdd.x += SPEED; break;
        case SDLK_s: toAdd.y -= SPEED; break;
        case SDLK_w: toAdd.y += SPEED; break;

        case SDLK_LEFT: toAddA += 0.01; break;
        case SDLK_RIGHT: toAddA -= 0.01; break;
    }

    if (isUp){
        toAdd = -toAdd;
        toAddA = -toAddA;
    }
    game->velocity = game->velocity + toAdd;
    game->angularVelocity += toAddA;

}