#pragma once

class EventProcessor;

#include <SFML/Graphics.hpp>
#include <vector>
#include "MathUtil.h"
#include "Drawer.h"
#include "EventProcessor.h"
#include "Player.h"


#define ASSERT_NO_NULL(ptr) if((ptr)==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(unsigned int w, unsigned int h);
    ~Game();
    void init();
    void run();
    void stop();
    void setCharacter(Player character);


    static void log(const std::string& status);
    static void error(const std::string& status);

private:
    friend class EventProcessor;
    void tick();

    Player character;
    char tickrate = 60.0;
    unsigned int width;
    unsigned int height;

    sf::RenderWindow *window{};

    Drawer *drawer{};
    EventProcessor *eventer{};
};
