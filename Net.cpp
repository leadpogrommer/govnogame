#include <thread>
#include "Net.h"
#include "Server.h"
#include "Game.h"

Net::Net(std::queue<Snapshot>* snaps, std::mutex snapsAccess) {
    this->snaps = snaps;
    this->snapsAccess = snapsAccess;

    auto result = this->announcer.listen(this->port);
    if (result != sf::Socket::Done) {
        Game.error(typeid(result).name());
    }

    std::stringstream ss;
    ss << "listening on port " << this->port;
    Game.log(ss.str());

    auto result = this->announcer.accept(this->client);
    if (result != sf::Socket::Done) {
        Game.error(typeid(result).name());
    }

    std::stringstream ss;
    ss << "client connected";
    Game.log(ss.str());

    this->announcerThread = std::thread(this.solve);
    this->announcerThread.detach();
}

Net::solve() {
    while (true) {
        this->snapsAccess.lock();
        struct Snapshot snap;
        if (this->snaps.empty() != true) {
            snap = this->snaps.front();
            this->snaps.pop();
        }
        this->snapsAccess.unlock();

        this->announcer.send(snap&, sizeof(snap));
    }
}