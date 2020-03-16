/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ClientNetwork
*/

#ifndef CLIENTNETWORK_HPP_
#define CLIENTNETWORK_HPP_

#include "../Network.hpp"
#include "../Connection/Tcp/TcpConnection.hpp"
#include "UdpClientConnection.hpp"

namespace rtype {
    namespace network {
        /**
         * @brief Main class of the Client network. It inherit of the Network
         * class and has to purpose of managing the network of the Client by
         * connecting to the Server and by receiving and sending packets from/to
         * the server
         *
         */
        class ClientNetwork : public Network {
            public:
                /**
                 * @brief Construct a new Client Network object
                 *
                 * @param port Port on which the client have to be connected.
                 * TCP is on port and UDP on port + 1
                 * @param readCallback This callback is called when a new packet
                 * has been received
                 */
                ClientNetwork(
                    const int & port, std::function<void(const protocol_t &, const std::string &)> readCallback,
                    std::function<void(void)> _connectCallback);

                /**
                 * @brief Destroy the Client Network object
                 *
                 */
                virtual ~ClientNetwork() = default;

                /**
                 * @brief Prepare the Client Network to connect to the Server
                 *
                 */
                void start();

				void initNetworkEndpoint(const int & port);

                /**
                 * @brief Get the Tcp Connection object
                 *
                 * @return const TcpConnection::pointer&
                 */
                const TcpConnection::pointer& getTcpConnection(void) const;

                /**
                 * @brief Get the Udp Connection object
                 *
                 * @return const UdpConnection::pointer&
                 */
                const UdpClientConnection::pointer& getUdpConnection(void) const;

                /**
                 * @brief clientId getter
                 *
                 * @return const unsigned ing
                 */
                unsigned int getClientId(void) const;

                /**
                 * @brief clientId setter
                 *
                 */
                void setClientId(const unsigned int &clientId);

                /**
                 * @brief clientId getter
                 *
                 * @return const unsigned ing
                 */
                std::string getClientName(void) const;

                /**
                 * @brief clientName setter
                 *
                 */
                void setClientName(const std::string &clientName);


            private:

                /**
                 * @brief Triggered when the Client has been connected
                 *
                 * @param error Encountered errors
                 */
                void handleConnect(const boost::system::error_code& error);


                unsigned int                            _clientId;
                std::string                             _clientName;

                std::function<void(
                    const protocol_t &, const std::string &)>   _readCallback;
                std::function<void(void)>                       _connectCallback;

                boost::asio::ip::tcp::endpoint          _tcpEndpoint;
                boost::asio::ip::udp::endpoint          _udpEndpoint;

                TcpConnection::pointer                  _tcpConnection;
                UdpClientConnection::pointer            _udpConnection;
        };
    }
}

#endif /* !CLIENTNETWORK_HPP_ */
