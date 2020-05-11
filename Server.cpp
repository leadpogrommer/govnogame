#include <queue>
#include <thread>
#include <chrono>
#include "Server.h"
#include "MathUtil.h"
#include "Net.h"
#include "Player.h"
#include "Game.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

Server::Server() {
//    this->snaps = std::queue<Snapshot>();
    this->snapsAccess = new std::mutex();

    this->announcer = new Net(&(this->toSend), this->snapsAccess, this);
    this->tickThread = std::thread(&Server::tick, this);

    std::stringstream ss;
    ss << "server created";
    Game::log(ss.str());
}

void Server::tick() {
    while (true) {

        govno.lock();
        for(auto &e: state.entities){
            e.second.tick(tickrate);
        }
        this->snapsAccess->lock();
        this->toSend.push(state);
        this->snapsAccess->unlock();
        govno.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/this->tickrate));
    }
}

uint16_t Server::addPlayer() {
    state.entities[nextPID] = Player();
    return nextPID++;
}

#pragma clang diagnostic pop