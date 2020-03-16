/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Network
*/

#include "Network.hpp"

namespace rtype {
    namespace network {
        Network::Network()
        {
        }

        void Network::poll(void)
        {
            _ioContext.poll();
        }

        void Network::sendTCPPacket(protocol_t &data, const TcpConnection::pointer &connection, const std::string &string)
        {
            communication_t message;
            
            std::memset(&(message), 0 , sizeof(communication_t));
            std::memcpy(&(message.protocol), &data, sizeof(protocol_t));
            std::memcpy(&(message.string), string.c_str(), string.size());

            boost::asio::mutable_buffers_1 buffer = boost::asio::buffer(&message, sizeof(communication_t));

            connection->startWrite(buffer);
        }

        void Network::sendUDPPacket(protocol_t &data, const UdpServerConnection::pointer &connection, const std::string &string)
        {
            communication_t message;

            std::memset(&(message), 0 , sizeof(communication_t));
            std::memcpy(&(message.protocol), &data, sizeof(protocol_t));
            std::memcpy(&(message.string), string.c_str(), string.size());

            boost::asio::mutable_buffers_1 buffer = boost::asio::buffer(&message, sizeof(communication_t));

            connection->startSend(buffer);
        }

        void Network::sendUDPPacket(protocol_t &data, const UdpClientConnection::pointer &connection, const std::string &string)
        {
            communication_t message;

            std::memset(&(message), 0 , sizeof(communication_t));
            std::memcpy(&(message.protocol), &data, sizeof(protocol_t));
            std::memcpy(&(message.string), string.c_str(), string.size());

            boost::asio::mutable_buffers_1 buffer = boost::asio::buffer(&message, sizeof(communication_t));

            connection->startSend(buffer);
        }
    }
}