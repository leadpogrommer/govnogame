#include "Server.h"

int main(int argc, char** argv){
    Server server;
    server.tickThread.join();
    return 0;
}