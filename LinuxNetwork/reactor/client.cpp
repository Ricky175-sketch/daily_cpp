#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // 替换为服务器监听的端口号
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // 替换为服务器的IP地址

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(sock);
        return 1;
    }

    std::string message;
    std::cout << "Enter a message to send to the server: ";
    std::getline(std::cin, message);

    send(sock, message.c_str(), message.length(), 0);

    char buffer[1024];
    int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        std::cerr << "Error receiving data from server" << std::endl;
    } else {
        buffer[bytes_received] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(sock);

    return 0;
}