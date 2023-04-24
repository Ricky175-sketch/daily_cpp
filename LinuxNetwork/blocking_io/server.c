#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024
#define SERVER_PORT 8080

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    socklen_t client_addr_size;

    // 创建服务器socket
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == -1) {
        perror("socket creation failed");
        exit(1);
    }

    // 设置服务器地址结构体
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // 绑定socket到服务器地址
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        exit(1);
    }

    // 监听socket
    if (listen(server_socket, 5) == -1) {
        perror("listen failed");
        exit(1);
    }

    client_addr_size = sizeof(client_addr);
    while (1) {
        // 接受客户端连接（阻塞式）
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
        if (client_socket == -1) {
            perror("accept failed");
            exit(1);
        }

        // 接收客户端消息并将其返回（阻塞式）
        int read_size;
        while ((read_size = read(client_socket, buffer, BUF_SIZE)) != 0) {
            printf("从客户端收到的消息：%s\n", buffer);
            write(client_socket, buffer, read_size);
            memset(buffer, 0, sizeof(buffer));
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}