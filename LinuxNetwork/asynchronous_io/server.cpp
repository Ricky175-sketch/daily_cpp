#include <iostream>
#include <asio.hpp>
#include <memory>
#include <thread>
#include <chrono>

using asio::ip::tcp;

class EchoSession : public std::enable_shared_from_this<EchoSession> {
public:
    EchoSession(tcp::socket socket)
        : socket_(std::move(socket)) {
    }

    void start() {
        read();
    }

private:
    void read() {
        auto self(shared_from_this());
        socket_.async_read_some(
            asio::buffer(data_, max_length),
            [this, self](const std::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    write(data_, bytes_transferred);
                }
            });
    }

    void write(const char* data, std::size_t bytes_transferred) {
        auto self(shared_from_this());
        asio::async_write(
            socket_,
            asio::buffer(data, bytes_transferred),
            [this, self](const std::error_code& error, std::size_t /*bytes_transferred*/) {
                if (!error) {
                    read();
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class EchoServer {
public:
    EchoServer(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        accept();
    }

private:
    void accept() {
        acceptor_.async_accept(
            [this](const std::error_code& error, tcp::socket socket) {
                if (!error) {
                    std::make_shared<EchoSession>(std::move(socket))->start();
                }

                accept();
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        asio::io_context io_context;
        EchoServer server(io_context, std::atoi(argv[1]));
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}