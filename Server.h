#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include "Player.h"
#include "Net.h"

class Server {
public:
    Server();
    void tick();
    const char tickrate = 60;

private:
    std::thread tickThread;
    std::queue<Snapshot> snaps;
    std::mutex snapsAccess;
    Net announcer;
    Player player;
};

struct Snapshot {
    float x;
    float y;
    float angle;
};