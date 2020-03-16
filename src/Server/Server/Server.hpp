/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "includes.hpp"

#include "ServerLobby.hpp"
#include "Communication.hpp"

#include "ServerNetwork.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "Parser.hpp"
#include "InputHandler.hpp"

#define GET_NETWORK this->getSceneManager().getNetwork()

namespace rtype {
    namespace server {
        #define DEFAULT_PORT 7171

        /**
         * @brief Main Server Class. It has to handle all the background work of
         * the RType project.
         *
         */
        class Server {
            public:
                /**
                 * @brief Functions on which are redirected the packets received
                 * by the Server in function of their opCode
                 *
                 */
                typedef void (Server::*opFunc)(const protocol_t &, const std::string &);

                /**
                 * @brief Construct a new Server object
                 *
                 */
                Server();

                /**
                 * @brief Destroy the Server object
                 *
                 */
                ~Server();

                /**
                 * @brief Main function of the Server. Contain a while loop in
                 * which all the sub functions are called
                 *
                 */
                void mainLoop(void);

                /**
                 * @brief Triggered when a new Client has been accepted on the
                 * Server
                 *
                 * @param connection TCP connection on which the client is
                 * connected
                 * @param clientId Id of the Client
                 */
                void acceptNetworkCallback(const network::TcpConnection::pointer &connection, const size_t & clientId);

                /**
                 * @brief Triggered when a new packet has been received on the
                 * Server
                 *
                 * @param data Data of the packet
                 * @param string Optional data string of the packet
                 */
                void readNetworkCallback(const protocol_t &data, const std::string &string);

                network::ServerNetwork * getNetwork() const;

                /**
                 * @brief Called when a Client is disconnected of the Server
                 *
                 * @param data Packet
                 * @param text Packet's text
                 */
                void opDisconnect(const protocol_t & data, const std::string & text);

            private:
                network::ServerNetwork *    _network;
                ServerLobby *               _lobby;

                std::map<const unsigned char, opFunc> _opFuncList;

                size_t                  _idClientCounter;
        };
    }
}

#endif /* !SERVER_HPP_ */
