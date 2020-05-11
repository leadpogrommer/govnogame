#include "EventProcessor.h"
#define SPEED 0.003
#define AS 0.001

#include "MathUtil.h"

EventProcessor::EventProcessor(Game *g): game(g), velocity(0, 0) {}

void EventProcessor::process() {
    sf::Event event{};
    while (game->window->pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                game->stop();
                break;

            case sf::Event::KeyPressed:
                processKey(event.key.code, false);
                break;
            case sf::Event::KeyReleased:
                processKey(event.key.code, true);
                break;
        }
    }
}

void EventProcessor::processKey(sf::Keyboard::Key k, bool isUp) {

    Vector2f toAdd(0, 0);
    float toAddA = 0.0;

    switch (k){
        case sf::Keyboard::A : toAdd.x -= SPEED; break;
        case sf::Keyboard::D : toAdd.x += SPEED; break;
        case sf::Keyboard::S: toAdd.y -= SPEED; break;
        case sf::Keyboard::W : toAdd.y += SPEED; break;

        case sf::Keyboard::Left: toAddA += AS; break;
        case sf::Keyboard::Right: toAddA -= AS; break;
    }

    if (isUp){
        toAdd = -toAdd;
        toAddA = -toAddA;
    }
    velocity += toAdd;
    aw += toAddA;
    game->sendSpeed(velocity);
    game->character.force(velocity);
    game->character.angularVelocity = aw;

}
