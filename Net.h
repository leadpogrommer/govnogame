#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <SFML/Network.hpp>
#include "Server.h"
#include <sstream>
#include "State.h"
#include <map>
#include <iostream>





class Server;
class Net {
public:
    Net(std::queue<State>* snaps, std::mutex* snapsAccess, Server* s);
    const int port = 1488;
    void stop() { isRunning = false; }
    
private:
    std::mutex* snapsAccess;
    std::queue<State>* toSend;
    std::thread announcerThread;
    std::thread accepterThread;
    sf::TcpListener announcer;
    bool isRunning = false;
    void solve();
    Server* server;
    std::mutex clientMapAccess;
    std::map<uint16_t, std::pair<sf::TcpSocket*, std::thread>> clients;
};