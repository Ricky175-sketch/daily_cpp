#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

constexpr auto DEFAULT_PORT = "3000";

void handleSession(websocket::stream<tcp::socket> ws) {
  try {
    ws.accept();
    auto remote_endpoint = ws.next_layer().lowest_layer().remote_endpoint();
    std::cout << "Connected to client: " << remote_endpoint << std::endl;

    for (;;) {
      beast::flat_buffer buffer;
      ws.read(buffer);

      auto message = beast::buffers_to_string(buffer.data());
      std::cout << "Received: " << message << std::endl;

      // Check if received message is browser information
      try {
        auto browser_info = json::parse(message);
        if (browser_info.contains("userAgent") && browser_info.contains("language") &&
            browser_info.contains("platform") && browser_info.contains("vendor")) {
          std::cout << "Browser Information:\n";
          std::cout << "  User Agent: " << browser_info["userAgent"].get<std::string>() << std::endl;
          std::cout << "  Language: " << browser_info["language"].get<std::string>() << std::endl;
          std::cout << "  Platform: " << browser_info["platform"].get<std::string>() << std::endl;
          std::cout << "  Vendor: " << browser_info["vendor"].get<std::string>() << std::endl;
          continue;
        }
      } catch (...) {
        // Not a valid JSON or not containing browser information
      }

      ws.text(ws.got_text());
      ws.write(buffer.data());
    }
  } catch (beast::system_error const &se) {
    if (se.code() != websocket::error::closed)
      std::cerr << "Error: " << se.code().message() << std::endl;
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main(int argc, char *argv[]) {
  try {
    auto const address = net::ip::make_address("0.0.0.0");
    auto const port = static_cast<unsigned short>(std::atoi(argc == 2 ? argv[1] : DEFAULT_PORT));

    net::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};
    std::cout << "WebSocket server is listening on " << address << ":" << port << std::endl;

    for (;;) {
      tcp::socket socket{ioc};
      acceptor.accept(socket);
      std::thread{handleSession, websocket::stream<tcp::socket>{std::move(socket)}}.detach();
    }
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
