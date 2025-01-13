#ifndef UDPSERVER_HPP_
    #define UDPSERVER_HPP_

#include <string>
#include <vector>
#include <asio.hpp>
#include <optional>

class UdpServer {
    public:
        UdpServer(const std::string &port);
        ~UdpServer();

        bool hasDataToRead(void);

        void sendTo(asio::ip::udp::endpoint const &endpoint, std::vector<uint8_t> const &data);
        void readFrom(asio::ip::udp::endpoint &endpoint, std::vector<uint8_t> &data);

    private:
        asio::io_context _io_context;
        asio::ip::udp::resolver _resolver;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::socket _socket;
};

#endif /* !UDPSERVER_HPP_ */
