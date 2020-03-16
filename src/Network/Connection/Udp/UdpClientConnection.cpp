/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** UdpClientConnection
*/

#include "UdpClientConnection.hpp"

namespace rtype {
    namespace network {
        UdpClientConnection::UdpClientConnection(
            boost::asio::io_context& ioContext,
            boost::asio::ip::udp::endpoint endpoint,
            std::function<void(const protocol_t &, const std::string &)> readCallback) :
            _socket(ioContext), _fillEndpoint(endpoint),
            _readCallback(readCallback)
        {
            _socket.open(boost::asio::ip::udp::v4());
        }

        UdpClientConnection::~UdpClientConnection()
        {
            _socket.close();
        }

        UdpClientConnection::pointer UdpClientConnection::create(
            boost::asio::io_context& ioContext,
            boost::asio::ip::udp::endpoint endpoint,
            std::function<void(const protocol_t &, const std::string &)> readCallback)
        {
            return pointer(new UdpClientConnection(
                ioContext, endpoint, readCallback));
        }

        void UdpClientConnection::startSend(const boost::asio::mutable_buffers_1 &buffer)
        {
            _socket.async_send_to(buffer, _fillEndpoint,
                boost::bind(&UdpClientConnection::handleSend, shared_from_this(),
                    boost::asio::placeholders::error));
        }

        void UdpClientConnection::startReceive(void)
        {
            boost::asio::mutable_buffers_1 buffer = boost::asio::buffer(_buffer, sizeof(communication_t));
            boost::asio::ip::udp::endpoint endpoint;

            _socket.async_receive_from(buffer, endpoint,
                boost::bind(&UdpClientConnection::handleReceive, shared_from_this(),
                    boost::asio::placeholders::error));
        }

        void UdpClientConnection::handleSend(
            const boost::system::error_code& error) const
        {
            if (error)
                std::cerr << error.message();
        }

        void UdpClientConnection::handleReceive(
            const boost::system::error_code& error)
        {
            communication_t message;

            if (!error) {
                std::memcpy(&message, _buffer, sizeof(communication_t));
                _readCallback(message.protocol, std::string(message.string));
                startReceive();
            } else
                std::cerr << error.message();
        }

        boost::asio::ip::udp::socket& UdpClientConnection::getSocket(void)
        {
            return _socket;
        }
    }
}