/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "../includes.hpp"
#include "../Network/Communication.hpp"

#include "INetwork.hpp"

namespace rtype {
    namespace network {
        /**
         * @brief Main class of the network. It permit to send and receive any
         * packet from Client to Server and conversely
         *
         */
        class Network : public INetwork {
            public:
                /**
                 * @brief Call the poll function of the ioContext
                 *
                 */
                void poll(void);

                /**
                 * @brief Send a TCP packet
                 *
                 * @param data Data of the packet
                 * @param connection Tcp connection through wich the packet will be send
                 * @param string Optional string of data for the packet
                 */
                void sendTCPPacket(protocol_t &data, const TcpConnection::pointer &connection, const std::string &string = "");

                /**
                 * @brief Send a UDP packet
                 *
                 * @param data Data of the packet
                 * @param connection Udp connection through wich the packet will be send
                 * @param string Optional string of data for the packet
                 */
                void sendUDPPacket(protocol_t &data, const UdpServerConnection::pointer &connection, const std::string &string = "");
                void sendUDPPacket(protocol_t &data, const UdpClientConnection::pointer &connection, const std::string &string = "");

            protected:
                /**
                 * @brief Construct a new Network object
                 *
                 */
                Network();

                /**
                 * @brief Destroy the Network object
                 *
                 */
                virtual ~Network() = default;

                boost::asio::io_context _ioContext;
        };
    }
}

#endif /* !NETWORK_HPP_ */
