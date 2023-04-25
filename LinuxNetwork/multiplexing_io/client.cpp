#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        return 1;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
        std::cerr << "Error: inet_pton failed" << std::endl;
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Error: connect failed" << std::endl;
        close(sockfd);
        return 1;
    }

    std::string message;
    char buffer[1024];

    while (true) {
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        ssize_t sent = send(sockfd, message.c_str(), message.size(), 0);
        if (sent == -1) {
            std::cerr << "Error: send failed" << std::endl;
            break;
        }

        ssize_t received = recv(sockfd, buffer, sizeof(buffer), 0);
        if (received == -1) {
            std::cerr << "Error: recv failed" << std::endl;
            break;
        }

        std::cout << "Server response: ";
        std::cout.write(buffer, received);
        std::cout << std::endl;
    }

    close(sockfd);
    return 0;
}
