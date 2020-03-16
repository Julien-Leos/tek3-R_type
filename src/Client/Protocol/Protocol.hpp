/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include "includes.hpp"
#include "Communication.hpp"
#include "guiGame.hpp"

namespace rtype {
namespace client {
    class Client;

    class Protocol {
        public:
            /**
             * @brief Functions on which are redirected the packets received
             * by the Client in function of their opCode
             *
             */
            typedef void (Protocol::*opFunc)(const protocol_t &, const std::string &);

            Protocol(const Client & client);
            virtual ~Protocol() = default;

            /**
             * @brief Browse all op codes through a function pointer map
             *
             * @param data Packet
             * @param string Packet's text
             */
            void    browseProtocols(const protocol_t &data, const std::string &text);

            /**
             * @brief Called when the Client connection is inilialized
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opInit(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the Client is connected to the Server
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opConnect(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the Client is disconnected of the Server
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opDisconnect(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the Client receive an object from the server
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opCreateObject(const protocol_t & data, const std::string &text);


            /**
             * @brief Called when a room is created
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opCreateRoom(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when a player joins a room
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opJoinRoom(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when a player leave a room
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opLeaveRoom(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when a room is deleted
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opDeleteRoom(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the client ask for the availables rooms
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opGetRoom(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when a player is ready
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opPlayerReady(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when a player is connecter to the room
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opGetPlayer(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when an object needs to be updated
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opUpdateObject(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when an object needs to be deleted
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opDeleteObject(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the game starts
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opStartGame(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the end starts
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opEndGame(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the score need to be updated
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opUpdateScore(const protocol_t & data, const std::string &text);

            /**
             * @brief Called when the health need to be updated
             *
             * @param data Packet
             * @param text Packet's text
             */
            void opUpdateHealth(const protocol_t & data, const std::string &text);

        private:
            const Client &                          _client;

            std::map<const unsigned char, opFunc>   _opFuncList;

    };
}
}

#endif /* !PROTOCOL_HPP_ */
