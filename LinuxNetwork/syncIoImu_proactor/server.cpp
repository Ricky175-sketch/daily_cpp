#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>

class session : public std::enable_shared_from_this<session> {
public:
    session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { read(); }

private:
    void read() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        read();
                                    }
                                });
    }

    boost::asio::ip::tcp::socket socket_;
    std::array<char, 1024> data_;
};

class server {
public:
    server(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        accept();
    }

private:
    void accept() {
        acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<session>(std::move(socket))->start();
            }

            accept();
        });
    }

    boost::asio::ip::tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        server srv(io_context, 8080);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}