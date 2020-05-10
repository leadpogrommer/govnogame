#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <SFML/Network.hpp>
#include "Server.h"
#include <sstream>


struct Snapshot;
class Net {
public:
    Net(std::queue<Snapshot>* snaps, std::mutex* snapsAccess);
    const int port = 1488;
    void stop(){isRunning = false;}

    
private:
    std::mutex *snapsAccess;
    std::queue<Snapshot>* snaps;
    std::thread announcerThread;
    sf::TcpListener announcer;
    sf::TcpSocket client;
    bool isRunning = false;
    void solve();
};