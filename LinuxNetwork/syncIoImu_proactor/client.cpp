#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>

void handle_connect(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Connected successfully" << std::endl;
    } else {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);

        // 将 handle_connect 与 async_connect 关联
        socket.async_connect(endpoint, boost::bind(&handle_connect, boost::asio::placeholders::error));

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}