/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ServerLobby
*/

#ifndef SERVER_LOBBY_HPP_
#define SERVER_LOBBY_HPP_

#include "../includes.hpp"
#include "ServerRoom.hpp"

namespace rtype {
    namespace server {
        class ServerLobby {
        public:
            ServerLobby(rtype::network::ServerNetwork *network);
            ~ServerLobby();

            void manageLobby(const protocol_t &data, const std::string &string);

        private:
            void connectPlayer(const std::string &clientName, const unsigned int &clientId);
            void disconnectPlayer(const unsigned int &clientId);
            void createRoom(const std::string &roomName, const unsigned int &clientId);
            void deleteRoom(const unsigned int &roomId);
            void getRooms(const unsigned int &clientId);
            void joinRoom(const unsigned int &roomId, const unsigned int &clientId);
            void leaveRoom(const unsigned int &roomId, const unsigned int &clientId);
            void playerReady(const unsigned int &roomId, const unsigned int &clientId);
            void getPlayers(const unsigned int &clientId, const unsigned int &roomId);

            unsigned int _nbRooms;
            std::vector<client_t> _clients;
            std::vector<ServerRoom *> _rooms;
            rtype::network::ServerNetwork *_network;

        };
    }
}

#endif /* !SERVER_LOBBY_HPP_ */
