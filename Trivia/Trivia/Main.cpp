#include "Server.h"
#include "WSAInitializer.h"

int main() {
    try {
        WSAInitializer WSAInit;
        Server server;
        server.run();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}