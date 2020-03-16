/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include "Communication.hpp"
#include "TcpConnection.hpp"
#include "UdpServerConnection.hpp"
#include "UdpClientConnection.hpp"

namespace rtype {
    namespace network {
        #define SERVER_IP "127.0.0.1"
		#define MESSAGE_SIZE 512

        /**
         * @brief Interface of the Network class
         *
         */
        class INetwork {
            public:
                /**
                 * @brief Call the poll function of the ioContext
                 *
                 */
                virtual void poll(void) = 0;

                /**
                 * @brief Send a TCP packet
                 *
                 * @param data Data of the packet
                 * @param connection Tcp connection through wich the packet will be send
                 * @param string Optional string of data for the packet
                 */
                virtual void sendTCPPacket(protocol_t &data, const TcpConnection::pointer &connection, const std::string &string = "") = 0;

                /**
                 * @brief Send a UDP packet
                 *
                 * @param data Data of the packet
                 * @param connection Udp connection through wich the packet will be send
                 * @param string Optional string of data for the packet
                 */
                virtual void sendUDPPacket(protocol_t &data, const UdpServerConnection::pointer &connection, const std::string &string = "") = 0;
                virtual void sendUDPPacket(protocol_t &data, const UdpClientConnection::pointer &connection, const std::string &string = "") = 0;
        };
    }
}

#endif /* !INETWORK_HPP_ */