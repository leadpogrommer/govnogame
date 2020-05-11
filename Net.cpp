#include <thread>
#include "Net.h"
#include "Server.h"
#include "Game.h"

Net::Net(std::queue<Snapshot>* snaps, std::mutex* snapsAccess) {
    this->snaps = snaps;
    this->snapsAccess = snapsAccess;

    auto result = this->announcer.listen(this->port);
    if (result != sf::Socket::Done) {
        Game::error(typeid(result).name());
    }

    std::stringstream ss;
    ss << "listening on port " << this->port;
    Game::log(ss.str());

    result = this->announcer.accept(this->client);
    if (result != sf::Socket::Done) {
        Game::error(typeid(result).name());
    }

    ss.clear();
    ss << "client connected";
    Game::log(ss.str());

    this->announcerThread = std::thread(&Net::solve, this);
    this->announcerThread.detach();
}

void Net::solve() {
    isRunning = true;
    while (isRunning) {
        this->snapsAccess->lock();
        Snapshot snap {};
        if (!this->snaps->empty()) {
            snap = this->snaps->front();
            this->snaps->pop();
        }
        this->snapsAccess->unlock();

        this->client.send((void*)&snap, sizeof(snap));

    }

}