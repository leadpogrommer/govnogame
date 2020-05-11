#pragma once

#include <map>
#include <SFML/Network.hpp>
#include "Player.h"

class State {
public:
    State()= default;
    State(sf::Packet &p);
    std::map<uint16_t, Player> entities;

    void toPacket(sf::Packet &p);
};
