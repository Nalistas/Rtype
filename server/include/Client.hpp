/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Client
*/

#include <cstdint>
#include <string>

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

/**
 * @brief Client class on server side
 * This class is used to represent a client
 */
class Client {
    public:
        Client();
        ~Client();

        /**
         * @brief Get the Room Id object
         * @return uint8_t
         */
        uint8_t getRoomId() const;

        /**
         * @brief Get the Name object
         * @return std::string
         */
        std::string getName() const;

        /**
         * @brief Get the Ready object
         * @return bool
         */
        bool isReady() const;

        /**
         * @brief Set the Room Id object
         * @param roomId
         */
        void setRoomId(uint8_t roomId);

        /**
         * @brief Set the Name object
         * @param name
         */
        void setName(std::string name);

        /**
         * @brief Set the Ready object
         * @param ready
         */
        void setReady(bool ready);
    private:
        uint8_t _room_id;
        std::string _name;
        bool _ready;
};

#endif /* !CLIENT_HPP_ */
