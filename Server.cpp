#include <queue>
#include <thread>
#include <chrono>
#include "Server.h"
#include "MathUtil.h"
#include "Net.h"

Server::server() {
    this->snaps = std::queue();
    this->snapsAccess = std::mutex();

    this->player = Player(Vector2f(0.0, 0.0), 0.0);
    this->announcer = Net(this->snaps*, this->snapsAccess);
    this->tickThread = std::thread(tick)
}

Server::tick() {
    while (true) {
        this->player.tick(this->tickrate);
        struct Snapshot snap;
        snap.x = this->player.position.x;
        snap.y = this->player.position.y;
        snap.angle = this->player.angle;
        this->snapsAccess.lock();
        this->snaps*.push(snap);
        this->snapsAccess.unlock();

        std::this_thread::sleep_for((1000/this->tickrate)ms);
    }
}