#pragma once

class EventProcessor;

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "MathUtil.h"
#include "Drawer.h"
#include "EventProcessor.h"
#include "Player.h"
#include "State.h"
#include <thread>
#include <mutex>


#define ASSERT_NO_NULL(ptr) if((ptr)==nullptr) error();

#define MAP_SIZE 2

class Game {
public:
    Game(unsigned int w, unsigned int h, sf::IpAddress ip, unsigned short port);
    ~Game();
    void init();
    void run();
    void stop();


    static void log(const std::string& status);
    static void error(const std::string& status);

    void sendSpeed(Vector2f spd, float aw);

private:
    friend class EventProcessor;
    void tick();

//    Player character;
    Player character;

    State state;
    uint16_t ourId;
    sf::TcpSocket serverSocket;

    std::thread* receiverThread;
    sf::Packet receivedPacket;
    bool received = false;
    std::mutex rpm;


    char tickrate = 60.0;
    unsigned int width;
    unsigned int height;

    sf::RenderWindow *window{};

    Drawer *drawer{};
    EventProcessor *eventer{};
};
