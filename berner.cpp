#include "berner.hpp"
#include "Networking/ListeningSocket.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    HDE::ListeningSocket serverSocket(
        AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10
    );

    std::cout << "Server listening on port 8080..." << std::endl;

    while (true) {
        struct sockaddr_in client_address;
        socklen_t address_len = sizeof(client_address);

        int client_fd = accept(
            serverSocket.get_sock(),
            (struct sockaddr*)&client_address,
            &address_len
        );

        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        std::cout << "Client connected (fd: " << client_fd << ")" << std::endl;

        const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 2\r\n"
            "\r\n"
            "Hi";

        send(client_fd, response, strlen(response), 0);

        close(client_fd);
    }

    return 0;
}