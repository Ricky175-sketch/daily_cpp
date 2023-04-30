#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX_EVENTS 10

class Reactor {
public:
    Reactor() {
        _epoll_fd = epoll_create1(0);
        if (_epoll_fd == -1) {
            perror("epoll_create1");
            exit(EXIT_FAILURE);
        }
    }

    ~Reactor() {
        close(_epoll_fd);
    }

    void add_fd(int fd, uint32_t events) {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = events;
        if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1) {
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
        }
    }

    void del_fd(int fd) {
        if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
        }
    }

    void run() {
        std::vector<struct epoll_event> events(MAX_EVENTS);
        while (true) {
            int n = epoll_wait(_epoll_fd, events.data(), MAX_EVENTS, -1);
            if (n == -1) {
                perror("epoll_wait");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < n; i++) {
                if (events[i].events & EPOLLIN) {
                    handle_input(events[i].data.fd);
                } else if (events[i].events & EPOLLOUT) {
                    handle_output(events[i].data.fd);
                }
            }
        }
    }

    virtual void handle_input(int fd) = 0;
    virtual void handle_output(int fd) = 0;

private:
    int _epoll_fd;
};

class EchoReactor : public Reactor {
public:
    EchoReactor(int listen_fd) : _listen_fd(listen_fd) {
        add_fd(_listen_fd, EPOLLIN);
    }

    void handle_input(int fd) override {
    if (fd == _listen_fd) {
        struct sockaddr_in addr;
        socklen_t addrlen = sizeof(addr);
        int conn_fd = accept(_listen_fd, (struct sockaddr *)&addr, &addrlen);
        if (conn_fd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        make_socket_non_blocking(conn_fd);
        add_fd(conn_fd, EPOLLIN);
    } else {
        char buf[1024];
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n <= 0) {
            if (n < 0) perror("read");
            close(fd);
            del_fd(fd);
        } else {
            _out_buffers[fd] = std::string(buf, n);
            del_fd(fd);
            add_fd(fd, EPOLLOUT);
        }
    }
}

void handle_output(int fd) override {
    auto it = _out_buffers.find(fd);
    if (it != _out_buffers.end()) {
        ssize_t n = write(fd, it->second.c_str(), it->second.size());
        if (n <= 0) {
            if (n < 0) perror("write");
            close(fd);
            del_fd(fd);
        } else {
            it->second.erase(0, n);
            if (it->second.empty()) {
                del_fd(fd);
                add_fd(fd, EPOLLIN);
            }
        }
    }
}

private:
    int make_socket_non_blocking(int sfd) {
        int flags = fcntl(sfd, F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl");
            return -1;
        }

        flags |= O_NONBLOCK;
        if (fcntl(sfd, F_SETFL, flags) == -1) {
            perror("fcntl");
            return -1;
        }

        return 0;
    }

    int _listen_fd;
    std::map<int, std::string> _out_buffers;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        exit(EXIT_FAILURE);
    }

    int port = std::stoi(argv[1]);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    EchoReactor echo_reactor(listen_fd);
    echo_reactor.run();

    return 0;
}