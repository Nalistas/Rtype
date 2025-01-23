#ifndef UDPSERVER_HPP_
    #define UDPSERVER_HPP_

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <string>
#include <vector>
#include <asio.hpp>
#include <optional>

/**
 * @brief The UdpServer class
 * This class is used to create a UDP server
 */
class UdpServer {
    public:
        /**
         * @brief Construct a new Udp Server object
         * it will loop from the port 2000 to the port 9999 to find an available port
         */
        UdpServer(void);

        /**
         * @brief Construct a new Udp Server object
         * @param port the port of the server
         */
        UdpServer(int port);

        /**
         * @brief Destroy the Udp Server object
         */
        ~UdpServer();

        /**
         * @brief Check if the server has data to read
         * @return true if the server has data to read
         * @return false if the server doesn't have data to read
         */
        bool hasDataToRead(void);

        /**
         * @brief Send data to a client
         * @param endpoint the endpoint of the client
         * @param data the data to send
         */
        void sendTo(asio::ip::udp::endpoint const &endpoint, std::vector<uint8_t> const &data);

        /**
         * @brief Receive data from a client
         * @param endpoint the endpoint of the client
         * @param data the data to receive
         */
        void readFrom(asio::ip::udp::endpoint &endpoint, std::vector<uint8_t> &data);

        /**
         * @brief Get the endpoint of the server
         * @return asio::ip::udp::endpoint the endpoint of the server
         */
        asio::ip::udp::endpoint getEndpoint(void) const;

    private:
        asio::io_context _io_context;
        asio::ip::udp::resolver _resolver;
        asio::ip::udp::endpoint _endpoint;
        asio::ip::udp::socket _socket;
};

#endif /* !UDPSERVER_HPP_ */
