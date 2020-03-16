/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** UdpServerConnection
*/

#include "UdpServerConnection.hpp"

namespace rtype {
    namespace network {
        UdpServerConnection::UdpServerConnection(
            boost::asio::io_context& ioContext,
            boost::asio::ip::udp::endpoint serverEndpoint,
            std::function<void(const protocol_t &, const std::string &)> readCallback) :
            _socket(ioContext, serverEndpoint), _readCallback(readCallback)
        {
        }

        UdpServerConnection::~UdpServerConnection()
        {
            _socket.close();
        }

        UdpServerConnection::pointer UdpServerConnection::create(
            boost::asio::io_context& ioContext,
            boost::asio::ip::udp::endpoint endpoint,
            std::function<void(const protocol_t &, const std::string &)> readCallback)
        {
            return pointer(new UdpServerConnection(
                ioContext, endpoint, readCallback));
        }

        void UdpServerConnection::startSend(const boost::asio::mutable_buffers_1 &buffer)
        {
            for (auto const& endpoint : _clientEndpoints) {
                _socket.async_send_to(buffer, endpoint.second,
                    boost::bind(&UdpServerConnection::handleSend, shared_from_this(),
                        boost::asio::placeholders::error));
            }
        }

        void UdpServerConnection::startReceive(void)
        {
            boost::asio::mutable_buffers_1 buffer = boost::asio::buffer(_buffer, sizeof(communication_t));

            _socket.async_receive_from(buffer, _endpoint,
                boost::bind(&UdpServerConnection::handleReceive, shared_from_this(),
                    boost::asio::placeholders::error));
        }

        void UdpServerConnection::handleSend(
            const boost::system::error_code& error) const
        {
            if (error)
                std::cerr << error.message();
        }

        void UdpServerConnection::handleReceive(
            const boost::system::error_code& error)
        {
            communication_t message;

            if (!error) {
                std::memcpy(&message, _buffer, sizeof(communication_t));
                addEndpoint(message.protocol.clientId, _endpoint);
                _readCallback(message.protocol, std::string(message.string));
                startReceive();
            } else
                std::cerr << error.message();
        }

        boost::asio::ip::udp::socket& UdpServerConnection::getSocket(void)
        {
            return _socket;
        }

        std::map<int, boost::asio::ip::udp::endpoint> & UdpServerConnection::getClientEndpoints(void)
        {
            return _clientEndpoints;
        }

        void UdpServerConnection::addEndpoint(int id, boost::asio::ip::udp::endpoint newEndpoint)
        {
            for (auto const& endpoint : _clientEndpoints) {
                if (endpoint.second == newEndpoint) {
                    return;
                }
            }
            _clientEndpoints.insert(std::pair<int, boost::asio::ip::udp::endpoint>(id, newEndpoint));
        }
    }
}