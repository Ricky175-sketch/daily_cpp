#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/select.h>

#define BUF_SIZE 1024
#define SERVER_PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    fd_set read_fds, temp_fds;
    int max_fd;

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

    // 设置客户端socket为非阻塞模式
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

    FD_ZERO(&read_fds);
    FD_SET(client_socket, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    max_fd = client_socket;

    while (1) {
        temp_fds = read_fds;

        // 使用select()函数监控文件描述符集合
        if (select(max_fd + 1, &temp_fds, NULL, NULL, NULL) == -1) {
            perror("select failed");
            exit(1);
        }

        if (FD_ISSET(STDIN_FILENO, &temp_fds)) {
            printf("请输入消息：");
            fgets(buffer, BUF_SIZE, stdin);
            buffer[strlen(buffer) - 1] = '\0';

            // 向服务器发送消息
            write(client_socket, buffer, strlen(buffer));
        }

        if (FD_ISSET(client_socket, &temp_fds)) {
            // 接收服务器响应（非阻塞式）
            int read_size = read(client_socket, buffer, BUF_SIZE - 1);
            if (read_size <= 0) {
                close(client_socket);
                exit(1);
            }

            buffer[read_size] = '\0';
            printf("从服务器接收到的消息：%s\n", buffer);
        }
    }

    close(client_socket);
    return 0;
}
