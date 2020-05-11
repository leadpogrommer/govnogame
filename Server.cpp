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

Server::Server(): player(Player(Vector2f(0, 0), 0.0)) {
    this->snaps = std::queue<Snapshot>();
    this->snapsAccess = new std::mutex();

    this->announcer = new Net(&(this->snaps), this->snapsAccess);
    this->tickThread = std::thread(&Server::tick, this);

    std::stringstream ss;
    ss << "server created";
    Game::log(ss.str());
}

void Server::tick() {
    while (true) {
        struct Snapshot snap;
        snap.x = this->player.position.x;
        snap.y = this->player.position.y;
        snap.angle = this->player.angle;
        this->snapsAccess->lock();
        this->snaps.push(snap);
        this->snapsAccess->unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/this->tickrate));
    }
}

#pragma clang diagnostic pop