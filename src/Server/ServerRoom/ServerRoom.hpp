/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Room
*/

#ifndef SERVER_ROOM_HPP_
#define SERVER_ROOM_HPP_

#include "includes.hpp"
#include "ServerNetwork.hpp"
#include "Communication.hpp"
#include "GameThread.hpp"

namespace rtype {
    namespace server {

#define DEFAULT_PORT 7171

        typedef struct client_s {
            unsigned int id;
            std::string name;
            bool isReady;
        } client_t;

        class ServerRoom {
        public:
            ServerRoom(const std::string &name, const unsigned int &id, rtype::network::ServerNetwork *network);
            ~ServerRoom();

            unsigned int getId(void);
            std::string getName(void);
            std::string getClientNameByClientId(const unsigned int &clientId);
            void joinRoom(const client_t &client);
            void leaveRoom(const unsigned int &clientId);
            void playerReady(const unsigned int &clientId);
            void getPlayers(const unsigned int &clientId);
            void startNewGameThread(void);

        private:
            rtype::network::ServerNetwork *_network;
            std::vector<client_t> _clients;
            const unsigned int _id;
            const std::string _name;
        };
    }
}

#endif /* !SERVER_ROOM_HPP_ */
