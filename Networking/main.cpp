#include <iostream>
#include "ListeningSocket.hpp"

int main() {
    HDE::ListeningSocket server(
        AF_INET,        // IPv4
        SOCK_STREAM,    // TCP
        0,              // Default protocol
        8080,           // Port
        INADDR_ANY,     // Listen on all interfaces
        10              // Backlog
    );

    std::cout << "Server successfully started on port 8080!" << std::endl;

    while (true) {
        // Keep the server alive so you can test it.
    }

    return 0;
}