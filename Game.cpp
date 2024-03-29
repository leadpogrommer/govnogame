#include "Game.h"
#include <string>
#include <iostream>
#include <cmath>

Game::Game(unsigned int w, unsigned int h, sf::IpAddress ip, unsigned short port) {
    this->width = w;
    this->height = h;
    serverSocket.connect(ip, port);
}

void Game::error(const std::string& status) {
    std::cout << "[ERROR]" << "\t";
    std::cout << status << std::endl;

    throw std::exception();
}

void Game::log(const std::string& status) {
    std::cout << "[LOG]" << "\t";
    std::cout << status << std::endl;
}

void Game::stop() {
    window->close();
}

void Game::run() {
    sf::Clock clock;


    while (window->isOpen()) {
        clock.restart();
        tick();

        auto tickTime = clock.getElapsedTime();

//        std::cout << tickTime.asMilliseconds() / (1000.0f / (float)tickrate) << "%\t" <<tickTime.asMilliseconds() << std::endl;

        sf::sleep(sf::milliseconds(1000/tickrate));
    }
}

void Game::init() {
    window = new sf::RenderWindow(sf::VideoMode(width, height), "DICKS", sf::Style::Titlebar | sf::Style::Close);
    window->setKeyRepeatEnabled(false);
    auto icon = sf::Image();
    icon.loadFromFile("res/icon.jpg");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    drawer = new Drawer(window);
    eventer = new EventProcessor(this);

    sf::Packet id;
    serverSocket.receive(id);
    id >> ourId;
    std::cout << ourId << std::endl;

    receiverThread = new std::thread([&]{
        while (true){
            sf::Packet r;
            serverSocket.receive(r);
            rpm.lock();
            receivedPacket = r;
            received = true;
            rpm.unlock();
        }
    });

}


void Game::tick() {
    if(received){
        received = false;
        rpm.lock();
        state = State(receivedPacket);
        rpm.unlock();

    }
    if(state.entities.count(ourId) == 0)
        return;

    Vector2f oldVelocity = character.velocity;
    float oldAngularVelocity = character.angularVelocity;

    character = state.entities[ourId];
    character.velocity = oldVelocity;
    character.angularVelocity = oldAngularVelocity;


    eventer->process();

    character.tick(tickrate);

    drawer->render(character.position, character.angle, state.entities);

    state.entities[ourId] = character;
//    drawer->renderDebug(character.position, character.angle);
}

Game::~Game() {
    delete window;
    delete drawer;
    delete eventer;
}

void Game::sendSpeed(Vector2f spd, float aw) {
    sf::Packet packet;
    std::cout << spd.x << '\t' << spd.y << std::endl;
    packet << spd.x << spd.y << aw;
    serverSocket.send(packet);
}
