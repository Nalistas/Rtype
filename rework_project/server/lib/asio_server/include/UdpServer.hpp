#ifndef UDPSERVER_HPP_
    #define UDPSERVER_HPP_

#include <string>
#include <vector>
#include <asio.hpp>
#include <optional>

class UdpServer {
    public:
        UdpServer(void);
        UdpServer(int port);
        ~UdpServer();

        bool hasDataToRead(void);

        void sendTo(asio::ip::udp::endpoint const &endpoint, std::vector<char> const &data);
        void readFrom(asio::ip::udp::endpoint &endpoint, std::vector<char> &data);

        asio::ip::udp::endpoint getEndpoint(void) const;

    private:
        asio::io_context _io_context;
        asio::ip::udp::resolver _resolver;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::socket _socket;
};

#endif /* !UDPSERVER_HPP_ */
