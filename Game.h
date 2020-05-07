#pragma once

class EventProcessor;

#include <SFML/Graphics.hpp>
#include <vector>
#include "MathUtil.h"
#include "Drawer.h"
#include "EventProcessor.h"
#include "Player.h"


#define ASSERT_NO_NULL(ptr) if(ptr==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(int w, int h, char tickrate);
    ~Game();
    void init();
    void run();
    void stop();
    void setCharacter(Player character);

private:
    friend class EventProcessor;
    void tick();
    static void error(int status = 0);

    Player character;
    char tickrate = 60.0;
    bool isRunning;
    int width;
    int height;

    sf::RenderWindow *window;

    Drawer *drawer;
    EventProcessor *eventer;
};
