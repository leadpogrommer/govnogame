#include <thread>
#include "Net.h"
#include "Server.h"
#include "Game.h"
#include <iostream>

Net::Net(std::queue<State>* snaps, std::mutex* snapsAccess, Server* s): server(s) {
    this->toSend = snaps;
    this->snapsAccess = snapsAccess;

    auto result = this->announcer.listen(this->port);
    if (result != sf::Socket::Done) {
        Game::error(typeid(result).name());
    }

    std::stringstream ss;
    ss << "listening on port " << this->port;
    Game::log(ss.str());

    accepterThread = std::thread([&]{
        while (true){
            sf::TcpSocket* s = new sf::TcpSocket;
            announcer.accept(*s);
            Game::log("somebody connected");
            s->setBlocking(true);

            server->govno.lock();
            auto newID = server->addPlayer();
            std::cout << newID << std::endl;
            server->govno.unlock();
            sf::Packet p;
            p << newID;
            s->send(p);
            clientMapAccess.lock();
            clients[newID] = std::pair<sf::TcpSocket*, std::thread>(s, std::thread([this, newID]{
                while(true){
                    sf::Packet p;
                    clientMapAccess.lock();
                    sf::TcpSocket* cs = this->clients[newID].first;
                    clientMapAccess.unlock();
                    cs->receive(p);
                    Vector2f newSpeed;
                    p >> newSpeed.x >> newSpeed.y;
                    float aw;
                    p >> aw;
//                    Game::log("received data");
                    this->server->govno.lock();
                    this->server->state.entities[newID].velocity = newSpeed;
                    this->server->state.entities[newID].angularVelocity = aw;
                    this->server->govno.unlock();
                }
            }));
            clientMapAccess.unlock();
        }
    });

//    ss.clear();
//    ss << "client connected";
//    Game::log(ss.str());

    this->announcerThread = std::thread(&Net::solve, this);
    this->announcerThread.detach();
}

void Net::solve() {
    isRunning = true;
    while (isRunning) {

        bool needSend = false;
        State st;

        this->snapsAccess->lock();
        if (!this->toSend->empty()) {
            st = this->toSend->front();
            needSend = true;
            this->toSend->pop();
        }
        this->snapsAccess->unlock();
        if(needSend) {
            sf::Packet p;
            st.toPacket(p);
            clientMapAccess.lock();
            for(const auto &cp: clients){
                cp.second.first->send(p);
            }
            clientMapAccess.unlock();
        }
    }

}