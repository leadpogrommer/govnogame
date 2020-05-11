#include "State.h"

void State::toPacket(sf::Packet &p) {
    p << (uint16_t )entities.size();
    for (const auto &pair: entities){
        p<<pair.first;
        p<<pair.second.position.x;
        p<<pair.second.position.y;
    }
}

State::State(sf::Packet &p) {
    uint16_t size;
    p>>size;
    for(uint16_t i = 0; i < size; i++){
        uint16_t id;
        p >> id;
        float x, y;
        p >> x >> y;
        entities[id] = Player(Vector2f(x, y), 0);

    }
}
