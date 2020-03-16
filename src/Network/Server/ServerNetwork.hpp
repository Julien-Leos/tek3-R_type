/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ServerNetwork
*/

#ifndef SERVERNETWORK_HPP_
#define SERVERNETWORK_HPP_

#include "Network.hpp"
#include "TcpConnection.hpp"
#include "UdpServerConnection.hpp"

namespace rtype {
    namespace network {
        /**
         * @brief Main class of the Server network. It inherit of the Network
         * class and has to purpose of managing the network of the Server by
         * accepting new Client and by receiving and sending packets from/to any
         * client
         *
         */
        class ServerNetwork : public Network {
            public:
                /**
                 * @brief Construct a new Server Network object
                 *
                 * @param port Port on which the client have to be connected.
                 * TCP is on port and UDP on port + 1
                 * @param readCallback This callback is called when a new packet
                 * has been received
                 * @param acceptCallback This callback is called when a new
                 * client has been accepted
                 */
                ServerNetwork(
                    const int & port, size_t & idClientCounter, std::function<void(const protocol_t &, const std::string &)> readCallback,
                    std::function<void(const TcpConnection::pointer &, const size_t & clientId)> acceptCallback);

                /**
                 * @brief Destroy the Server Network object
                 *
                 */
                virtual ~ServerNetwork() = default;

                /**
                 * @brief Remove a TCP connection of the vector of TCP
                 * connection in function of her ID
                 *
                 * @param id Id of the TCP connection
                 */
                void removeTcpConnection(const size_t & id);

                /**
                 * @brief Get the Tcp Connection By Id object
                 *
                 * @param id Id of the TCP connection
                 * @return const TcpConnection::pointer
                 */
                const TcpConnection::pointer getTcpConnectionById(const size_t & id) const;

                /**
                 * @brief Get the Tcp Connections object
                 *
                 * @return const std::vector<TcpConnection::pointer>&
                 */
                const std::vector<TcpConnection::pointer>& getTcpConnections(void) const;

                /**
                 * @brief Get the Udp Connection object
                 *
                 * @return const UdpServerConnection::pointer&
                 */
                const UdpServerConnection::pointer& getUdpConnection(void) const;

                const std::vector<int> getClientsIds(void) const;

            private:
                /**
                 * @brief Prepare the Server Network to accept a new client's
                 * connection
                 *
                 */
                void startAccept();
                /**
                 * @brief Triggered when a new client has been accepted
                 *
                 * @param error Encountered errors
                 * @param clientId Id of the new client
                 */
                void handleAccept(const boost::system::error_code& error, const size_t & clientId);


                size_t &                        _idClientCounter;

                std::function<void(const protocol_t &, const std::string &)> _readCallback;
                std::function<void(const TcpConnection::pointer &, const size_t & clientId)> _acceptCallback;

                boost::asio::ip::tcp::acceptor  _tcpAcceptor;
                boost::asio::ip::udp::endpoint  _udpEndpoint;

                std::vector<TcpConnection::pointer>     _tcpConnections;
                UdpServerConnection::pointer            _udpConnection;
        };
    }
}

#endif /* !SERVERNETWORK_HPP_ */
