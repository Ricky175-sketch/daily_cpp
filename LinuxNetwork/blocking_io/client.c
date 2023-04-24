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
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // 创建客户端socket
    client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == -1) {
        perror("socket creation failed");
        exit(1);
    }

    // 设置服务器地址结构体
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(SERVER_PORT);

    // 连接到服务器（阻塞式）
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed");
        exit(1);
    }

    while (1) {
        printf("请输入消息：");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        // 向服务器发送消息
        write(client_socket, buffer, strlen(buffer));

        // 接收服务器响应（阻塞式）
        int read_size = read(client_socket, buffer, BUF_SIZE - 1);
        if (read_size == -1) {
            perror("read failed");
            exit(1);
        }

        buffer[read_size] = '\0';
        printf("从服务器接收到的消息：%s\n", buffer);
    }

    close(client_socket);
    return 0;
}