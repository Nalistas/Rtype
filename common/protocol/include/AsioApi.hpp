/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include <iostream>
#include <asio.hpp>
#include <vector>

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_


using asio::ip::udp;

namespace rtype_protocol {
    class AsioApi {
        public:

            /**
             * @brief Struct to store the data received
             */
            struct UDP_DATA {
                std::vector<char> data;
                udp::endpoint sender_endpoint;
            };

            /**
             * @brief Construct a new AsioApi object
             */
            AsioApi();

            /**
             * @brief Destroy the AsioApi object
             */
            ~AsioApi();

            /**
             * @brief Check if the client has data to read
             */
            bool has_data();

            /**
             * @brief Get the data from the server
             */
            UDP_DATA get_data();

            //////////////////////////////////////////////////////////////////////
            //                       CLIENT METHODS                             //
            //////////////////////////////////////////////////////////////////////
            /// @name CLIENT METHODS
            /// @{

            /**
             * @brief Send a message to the server
             */
            void send_message(const std::string &message);

            /**
             * @brief Connect to the server
             */
            bool connect(const std::string &ip, const std::string &port = "5000");


            /// @}
            ///////////////////////////////////////////////////////////////////////
            //                       SERVER METHODS                             //
            ///////////////////////////////////////////////////////////////////////
            /// @name SERVER METHODS
            /// @{

            /**
             * @brief Start the server
             */
            bool start_server(const std::string &port);

            /**
             * @brief Reply to a client
             */
            void reply_to(const UDP_DATA &client_data);

            /// @}



        private:
            asio::io_context io_context;
            udp::resolver resolver;
            udp::endpoint endpoint;
            udp::socket socket;
            bool connected;
    };
}

#endif /* !CLIENT_HPP_ */
