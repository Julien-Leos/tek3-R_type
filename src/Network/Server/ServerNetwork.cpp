/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** ServerNetwork
*/

#include "ServerNetwork.hpp"

namespace rtype {
    namespace network {
        ServerNetwork::ServerNetwork(
            const int & port, size_t & idClientCounter, std::function<void(const protocol_t &, const std::string &)> readCallback,
            std::function<void(const TcpConnection::pointer &, const size_t & clientId)> acceptCallback) :
            Network(), _idClientCounter(idClientCounter), _readCallback(readCallback), _acceptCallback(acceptCallback),
            _tcpAcceptor(_ioContext,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
            _udpEndpoint(
                boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port + 1))
        {
            _udpConnection = UdpServerConnection::create(
                _ioContext, _udpEndpoint, _readCallback);
            _udpConnection->startReceive();
            startAccept();
        }

        void ServerNetwork::removeTcpConnection(const size_t & id)
        {
            auto it = std::find(_tcpConnections.begin(), _tcpConnections.end(), getTcpConnectionById(id));
            int index = distance(_tcpConnections.begin(), it);

            _tcpConnections.erase(_tcpConnections.begin() + index);
        }

        const TcpConnection::pointer ServerNetwork::getTcpConnectionById(const size_t & id) const
        {
            for(auto const& connection: _tcpConnections) {
                if (connection->getId() == id)
                    return connection;
            }
            return boost::shared_ptr<TcpConnection>();
        }

        const std::vector<TcpConnection::pointer>& ServerNetwork::getTcpConnections(void) const
        {
            return _tcpConnections;
        }

        const UdpServerConnection::pointer& ServerNetwork::getUdpConnection(void) const
        {
            return _udpConnection;
        }

        const std::vector<int> ServerNetwork::getClientsIds(void) const
        {
            std::vector<int> clientIds;

            for (auto const &connection : _tcpConnections) {
                clientIds.push_back(connection->getId());
            }
            clientIds.pop_back();
            return clientIds;
        }

        void ServerNetwork::startAccept()
        {
            _tcpConnections.push_back(
                TcpConnection::create(_idClientCounter, _ioContext, _readCallback));

            _tcpAcceptor.async_accept(_tcpConnections.back()->getSocket(),
                boost::bind(&ServerNetwork::handleAccept,
                this, boost::asio::placeholders::error, _idClientCounter));
            _idClientCounter += 1;
        }

        void ServerNetwork::handleAccept(
            const boost::system::error_code& error, const size_t & clientId)
        {
            if (!error) {
                _tcpConnections.back()->startRead();
                _acceptCallback(_tcpConnections.back(), clientId);
                startAccept();
            } else
                std::cerr << error.message();
        }
    }
}