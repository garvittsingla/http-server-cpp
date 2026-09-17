#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main() {

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;        
    hints.ai_socktype = SOCK_STREAM;  

    int status = getaddrinfo("localhost", "8080", &hints, &result);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    int sockfd = socket(
        result->ai_family,
        result->ai_socktype,
        result->ai_protocol
    );

    if (sockfd == -1) {
        perror("socket");
        freeaddrinfo(result);
        return 1;
    }

    if (connect(sockfd, result->ai_addr, result->ai_addrlen) == -1) {
        perror("connect");
        close(sockfd);
        freeaddrinfo(result);
        return 1;
    }

    printf("Connected!\n");

    const char *request =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080/test\r\n"
        "Connection: close\r\n"
        "\r\n"
        "hey i am Garvit singla"
    ;

    send(sockfd, request, strlen(request), 0);

    char buffer[4096];
    ssize_t bytes_received;

    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    if (bytes_received == -1) {
        perror("recv");
    }

    close(sockfd);

}