/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Server
*/

#include "Server.hpp"

namespace rtype {
    namespace server {
        Server::Server()
        {
            _idClientCounter = 1;
            _network = new network::ServerNetwork(DEFAULT_PORT, _idClientCounter, [this](const protocol_t &data, const std::string &string){
                this->readNetworkCallback(data, string);
            }, [this](const network::TcpConnection::pointer &connection, const size_t & clientId){
                this->acceptNetworkCallback(connection, clientId);
            });
            _lobby = new ServerLobby(_network);

            _opFuncList.insert(std::make_pair(13, &Server::opDisconnect));
        }

        Server::~Server()
        {
            delete(_lobby);
            delete(_network);
        }

        void Server::readNetworkCallback(const protocol_t &data, const std::string &string)
        {
            auto opFunc = _opFuncList[data.opcode];

            if (data.opcode >= 10 && data.opcode < 30)
                _lobby->manageLobby(data, string);
            if (!opFunc)
                return;
            (this->*opFunc)(data, string);
        }

        void Server::acceptNetworkCallback(const network::TcpConnection::pointer &connection, const size_t & clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            data.opcode = 1;
            data.clientId = clientId;
            _network->sendTCPPacket(data, connection);
        }

        void Server::opDisconnect(const protocol_t & data, const std::string & text)
        {
            _network->removeTcpConnection(data.clientId);
            static_cast<void>(text);
        }

        void Server::mainLoop(void)
        {
            while (1)
                _network->poll();
        }

        network::ServerNetwork * Server::getNetwork() const
        {
            return _network;
        }
    }
}