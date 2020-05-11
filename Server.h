#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include "Player.h"
#include "Net.h"
#include "State.h"


class Net;

class Server {
public:
    Server();
    void tick();
    const char tickrate = 60;
    uint16_t addPlayer();
    std::mutex govno;
    std::thread tickThread;

private:
    friend class Net;
    uint16_t nextPID = 0;

    std::queue<State> toSend;
    std::mutex* snapsAccess;

    Net* announcer;
    State state;
};
