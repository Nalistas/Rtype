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

class Client {
    public:
        Client();
        ~Client();

        uint8_t getRoomId() const;
        void setRoomId(uint8_t roomId);
        std::string getName() const;
        void setName(std::string name);
        bool isReady() const;
        void setReady(bool ready);
    private:
        uint8_t _room_id;
        std::string _name;
        bool _ready;
};

#endif /* !CLIENT_HPP_ */
