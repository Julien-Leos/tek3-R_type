/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Lobby
*/

#include "ServerLobby.hpp"

namespace rtype {
    namespace server {
        ServerLobby::ServerLobby(rtype::network::ServerNetwork *network) : _nbRooms(0)
        {
            _network = network;
        }

        ServerLobby::~ServerLobby()
        {
        }

        void ServerLobby::manageLobby(const protocol_t &data, const std::string &string)
        {
            if (data.opcode == 11)
                this->connectPlayer(string, data.clientId);
            else if (data.opcode == 12)
                this->disconnectPlayer(data.clientId);
            else if (data.opcode == 21)
                this->createRoom(string, data.clientId);
            else if (data.opcode == 22)
                this->joinRoom(data.data, data.clientId);
            else if (data.opcode == 23)
                this->leaveRoom(data.data, data.clientId);
            else if (data.opcode == 24)
                this->deleteRoom(data.data);
            else if (data.opcode == 25)
                this->getRooms(data.clientId);
            else if (data.opcode == 26)
                this->playerReady(data.data, data.clientId);
            else if (data.opcode == 27)
                this->getPlayers(data.clientId, data.data);
        }

        void ServerLobby::connectPlayer(const std::string &clientName, const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);
            client_t newClient;


            newClient.id = clientId;
            newClient.name = clientName;
            _clients.push_back(newClient);
            data.opcode = 11;
            data.data = newClient.id;
            _network->sendTCPPacket(data, _network->getTcpConnectionById(newClient.id), clientName);
            this->getRooms(clientId);
        }

        void ServerLobby::disconnectPlayer(const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            for(unsigned int i = 0; i < _clients.size(); i++) {
                if (_clients[i].id == clientId) {
                    data.opcode = 12;
                    _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients[i].id));
                    _clients.erase(_clients.begin() + i);
                    break;
                }
            }
        }

        void ServerLobby::createRoom(const std::string &roomName, const unsigned int &clientId)
        {
            ServerRoom *newRoom = new ServerRoom(roomName, _nbRooms, _network);
            protocol_t data;
            EMPTY_PROTOCOL(data);

            _rooms.push_back(newRoom);
            _nbRooms += 1;
            data.opcode = 21;
            data.data = newRoom->getId();
            for(unsigned int i = 0; i < _clients.size(); i++) {
                _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id), roomName);
            }
            this->joinRoom(newRoom->getId(), clientId);
        }

        void ServerLobby::deleteRoom(const unsigned int &roomId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            for(unsigned int i = 0; i < _rooms.size(); i++) {
                if (_rooms[i]->getId() == roomId) {
                    data.opcode = 24;
                    data.data = _rooms[i]->getId();
                    _rooms.erase(_rooms.begin() + i);
                    for(unsigned int i = 0; i < _clients.size(); i++) {
                        _network->sendTCPPacket(data, _network->getTcpConnectionById(_clients.at(i).id));
                    }
                    break;
                }
            }
        }

        void ServerLobby::getRooms(const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            data.opcode = 25;
            for(unsigned int i = 0; i < _rooms.size(); i++) {
                data.data = _rooms[i]->getId();
                _network->sendTCPPacket(data, _network->getTcpConnectionById(clientId), _rooms[i]->getName());
            }
        }

        void ServerLobby::joinRoom(const unsigned int &roomId, const unsigned int &clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            data.opcode = 22;
            data.data = roomId;
            _network->sendTCPPacket(data, _network->getTcpConnectionById(clientId));
            for(unsigned int i = 0; i < _rooms.size(); i++) {
                if (_rooms[i]->getId() == roomId) {
                    for(unsigned int j = 0; j < _clients.size(); j++) {
                        if (_clients[j].id == clientId) {
                            _rooms[i]->joinRoom(_clients[j]);
                            _clients.erase(_clients.begin() + j);
                            break;
                        }
                    }
                    break;
                }
            }
            this->getPlayers(clientId, roomId);
        }

        void ServerLobby::leaveRoom(const unsigned int &roomId, const unsigned int &clientId)
        {
            client_t newClient;

            for(unsigned int i = 0; i < _rooms.size(); i++) {
                if (_rooms[i]->getId() == roomId) {
                    newClient.name = _rooms[i]->getClientNameByClientId(clientId);
                    newClient.id = clientId;
                    _rooms[i]->leaveRoom(clientId);
                    _clients.push_back(newClient);
                    break;
                }
            }
            this->getRooms(clientId);
        }

        void ServerLobby::playerReady(const unsigned int &roomId, const unsigned int &clientId)
        {
            for(unsigned int i = 0; i < _rooms.size(); i++) {
                if (_rooms[i]->getId() == roomId) {
                    _rooms[i]->playerReady(clientId);
                    break;
                }
            }
        }

        void ServerLobby::getPlayers(const unsigned int &clientId, const unsigned int &roomId)
        {
            for(unsigned int i = 0; i < _rooms.size(); i++) {
                if (_rooms[i]->getId() == roomId) {
                    _rooms[i]->getPlayers(clientId);
                    break;
                }
            }
        }
    }
}