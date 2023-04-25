#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

const int MAX_EVENTS = 10;

int make_socket_non_blocking(int sfd) {
    int flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "Error: fcntl failed" << std::endl;
        return -1;
    }

    flags |= O_NONBLOCK;
    if (fcntl(sfd, F_SETFL, flags) == -1) {
        std::cerr << "Error: fcntl failed" << std::endl;
        return -1;
    }
    return 0;
}

int main() {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        std::cerr << "Error: socket creation failed" << std::endl;
        return 1;
    }

    if (make_socket_non_blocking(sfd) == -1) {
        close(sfd);
        return 1;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    if (bind(sfd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Error: bind failed" << std::endl;
        close(sfd);
        return 1;
    }

    if (listen(sfd, SOMAXCONN) == -1) {
        std::cerr << "Error: listen failed" << std::endl;
        close(sfd);
        return 1;
    }

    int efd = epoll_create1(0);
    if (efd == -1) {
        std::cerr << "Error: epoll_create1 failed" << std::endl;
        close(sfd);
        return 1;
    }

    epoll_event event;
    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event) == -1) {
        std::cerr << "Error: epoll_ctl failed" << std::endl;
        close(sfd);
        close(efd);
        return 1;
    }

    epoll_event events[MAX_EVENTS];

    while (true) {
        int n = epoll_wait(efd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; ++i) {
            if (events[i].data.fd == sfd) {
                // 新连接
                while (true) {
                    sockaddr in_addr;
                    socklen_t in_len = sizeof(in_addr);
                    int infd = accept(sfd, &in_addr, &in_len);
                    if (infd == -1) {
                        break;
                    }

                    if (make_socket_non_blocking(infd) == -1) {
                        close(infd);
                        continue;
                    }
                    epoll_event event;
                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    if (epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event) == -1) {
                        std::cerr << "Error: epoll_ctl failed" << std::endl;
                        close(infd);
                        continue;
                    }
                }
            } else {
                // 处理已连接的客户端
                char buf[1024];
                ssize_t count = 0;
                while (true) {
                    count = read(events[i].data.fd, buf, sizeof(buf));
                    if (count <= 0) {
                        break;
                    }

                    // 回显数据
                    ssize_t written = 0;
                    while (written < count) {
                        ssize_t n = write(events[i].data.fd, buf + written, count - written);
                        if (n == -1) {
                            break;
                        }
                        written += n;
                    }
                }

                if (count == 0 || (count == -1 && errno != EAGAIN)) {
                    // 断开连接
                    close(events[i].data.fd);
                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
                }
            }
        }
    }

    close(sfd);
    close(efd);
    return 0;
}
