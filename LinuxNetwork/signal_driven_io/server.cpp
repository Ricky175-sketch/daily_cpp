#include <iostream>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

void sigio_handler(int sig);

int sockfd;

int main() {
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Unable to create socket" << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Unable to bind socket" << std::endl;
        return 1;
    }

    if (listen(sockfd, 5) < 0) {
        std::cerr << "Error: Unable to listen on socket" << std::endl;
        return 1;
    }

    signal(SIGIO, sigio_handler);
    fcntl(sockfd, F_SETOWN, getpid());
    int flags = fcntl(sockfd, F_GETFL);
    fcntl(sockfd, F_SETFL, flags | O_ASYNC);

    while (1) {
        pause();
    }

    return 0;
}

void sigio_handler(int sig) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        std::cerr << "Error: Unable to accept connection" << std::endl;
        return;
    }

    char buffer[256];
    memset(buffer, 0, 256);
    int n = read(client_socket, buffer, 255);
    if (n < 0) {
        std::cerr << "Error: Unable to read from client" << std::endl;
        return;
    }

    std::cout << "Received message: " << buffer << std::endl;

    close(client_socket);
}