/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ClientNetwork
*/

#include "ClientNetwork.hpp"

namespace rtype {
    namespace network {
        ClientNetwork::ClientNetwork(
            const int & port, std::function<void(const protocol_t &, const std::string &)> readCallback,
            std::function<void(void)> connectCallback) :
            Network(), _readCallback(readCallback), _connectCallback(connectCallback)
        {
            initNetworkEndpoint(port);
            start();
        }

        void ClientNetwork::initNetworkEndpoint(const int & port)
        {
            _tcpEndpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(SERVER_IP), port);
            _udpEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(SERVER_IP), port + 1);
        }

        unsigned int ClientNetwork::getClientId(void) const
        {
            return _clientId;
        }

        void ClientNetwork::setClientId(const unsigned int &clientId)
        {
            _clientId = clientId;
        }

        std::string ClientNetwork::getClientName(void) const
        {
            return _clientName;
        }

        void ClientNetwork::setClientName(const std::string &clientName)
        {
            _clientName = clientName;
        }

        const TcpConnection::pointer& ClientNetwork::getTcpConnection(void) const
        {
            return _tcpConnection;
        }

        const UdpClientConnection::pointer& ClientNetwork::getUdpConnection(void) const
        {
            return _udpConnection;
        }

        void ClientNetwork::start()
        {
            _udpConnection = UdpClientConnection::create(
                _ioContext, _udpEndpoint, _readCallback);
            _udpConnection->startReceive();

            _tcpConnection = TcpConnection::create(0, _ioContext, _readCallback);

            _tcpConnection->getSocket().async_connect(_tcpEndpoint,
                boost::bind(&ClientNetwork::handleConnect,
                this, boost::asio::placeholders::error));
        }

        void ClientNetwork::handleConnect(
            const boost::system::error_code& error)
        {
            if (!error) {
                _connectCallback();
                _tcpConnection->startRead();
            } else
                std::cerr << error.message();
        }
    }
}
