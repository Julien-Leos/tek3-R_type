/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ServerRoom
*/

#include "ServerRoom.hpp"

namespace rtype {
    namespace server {
        ServerRoom::ServerRoom(const std::string &name, const unsigned int &id, rtype::network::ServerNetwork *network) : _id(id), _name(name)
        {
            _network = network;
        }

        ServerRoom::~ServerRoom()
        {
        }

        unsigned int ServerRoom::getId(void)
        {
            return _id;
        }

        std::string ServerRoom::getName(void)
        {
            return (_name);
        }

        std::string ServerRoom::getClientNameByClientId(const unsigned int &clientId)
        {
            for(unsigned int i = 0; i < _clients.size(); i++)
            {
                if (_clients[i].id == clientId)
                {
                    return (_clients[i].name);
                }
            }
            return (std::string(""));
        }

        void ServerRoom::joinRoom(const rtype::server::client_t &client)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);
            client_t newClient;

            newClient.id = client.id;
            newClient.name = client.name;
            newClient.isReady = 0;
            data.opcode = 27;
            data.data = client.id;
            for(unsigned int i = 0; i < _clients.size(); i++)
            {
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id), newClient.name);
            }
            _clients.push_back(newClient);
        }

        void ServerRoom::leaveRoom(const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);
            unsigned int i = 0;

            for(; i < _clients.size(); i++)
            {
                if (_clients.at(i).id == clientId)
                    break;
            }
            data.opcode = 23;
            data.data = clientId;
            _network->sendTCPPacket(data, _network->getTcpConnectionById(clientId));
            for(unsigned int j = 0; j < _clients.size(); j++)
            {
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(j).id), _clients.at(i).name);
            }
            _clients.erase(_clients.begin() + i);

        }

        void ServerRoom::playerReady(const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);
            int start = 1;

            data.opcode = 26;
            data.data = clientId;
            for(unsigned int i = 0; i < _clients.size(); i++) {
                if (_clients[i].id == clientId)
                    _clients[i].isReady = 1;
                if (_clients.at(i).isReady == 0)
                    start = 0;
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id));
            }
            if (start == 1)
                this->startNewGameThread();
        }

        void ServerRoom::getPlayers(const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            data.opcode = 27;
            for (unsigned int i = 0; i < _clients.size(); i++) {
                data.data = _clients.at(i).id;
                _network->sendTCPPacket(data, _network->getTcpConnectionById(clientId), _clients.at(i).name);
            }
        }

        void ServerRoom::startNewGameThread(void)
        {
            const unsigned int port = DEFAULT_PORT + 2 + _id * 2;
            size_t _idClientCounter = 1;
            protocol_t data;
            EMPTY_PROTOCOL(data);

            std::thread newThread([](const unsigned int port, size_t idClientCounter, const int & nbPlayers) {
                GameThread game(port, idClientCounter, nbPlayers);
                game.mainLoop();
            }, port, _idClientCounter, _clients.size());
            newThread.detach();

            for (unsigned int i = 0; i < _clients.size(); i++) {
                data.opcode = 24;
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id));
                data.opcode = 31;
                data.data = port;
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id));
            }
        }
    }
}