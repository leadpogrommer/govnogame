#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <SFML/Network.hpp>
#include <Server.h>
#include <sstream>

class Net {
public:
    Net(std::queue<Snapshot>* snaps, std::mutex snapsAccess);
    const int port = 1488;
    
private:
    std::mutex snapsAccess;
    std::queue<Snapshot>* snaps;
    std::thread announcerThread;
    sf::TcpListener announcer;
    sf::TcpSocket client;
    void solve();
};