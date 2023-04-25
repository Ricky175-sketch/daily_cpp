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
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    socklen_t client_addr_size;
    fd_set read_fds, temp_fds;
    int max_fd;

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

    // 设置服务器socket为非阻塞模式
    int flags = fcntl(server_socket, F_GETFL, 0);
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK);

    FD_ZERO(&read_fds);
    FD_SET(server_socket, &read_fds);
    max_fd = server_socket;

    client_addr_size = sizeof(client_addr);
    while (1) {
        temp_fds = read_fds;

        // 使用select()函数监控文件描述符集合
        if (select(max_fd + 1, &temp_fds, NULL, NULL, NULL) == -1) {
            perror("select failed");
            exit(1);
        }

        for (int i = 0; i <= max_fd; i++) {
            if (FD_ISSET(i, &temp_fds)) {
                if (i == server_socket) {
                    // 接受客户端连接（非阻塞式）
                    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
                    if (client_socket == -1) {
                        perror("accept failed");
                        exit(1);
                    }

                    // 将客户端socket添加到文件描述符集合
                    FD_SET(client_socket, &read_fds);
                    if (client_socket > max_fd) {
                        max_fd = client_socket;
                    }
                } else {
                    // 接收客户端消息并将其返回（非阻塞式）
                    int read_size = read(i, buffer, BUF_SIZE - 1);
                    if (read_size <= 0) {
                        close(i);
                        FD_CLR(i, &read_fds);
                    } else {
                        write(i, buffer, read_size);
                    }
                }
            }
        }
    }

    close(server_socket);
    return 0;
}
