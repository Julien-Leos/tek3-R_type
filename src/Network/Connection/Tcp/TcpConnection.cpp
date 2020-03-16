/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"

namespace rtype {
    namespace network {
        TcpConnection::TcpConnection(
            const size_t & clientId,
            boost::asio::io_context& ioContext,
            std::function<void(const protocol_t &, const std::string &)> readCallback) :
            _id(clientId), _socket(ioContext), _readCallback(readCallback)
        {
        }

        TcpConnection::~TcpConnection()
        {
            _socket.close();
        }

        TcpConnection::pointer TcpConnection::create(
            const size_t & clientId,
            boost::asio::io_context& ioContext,
            std::function<void(const protocol_t &, const std::string &)> readCallback)
        {
            return pointer(new TcpConnection(clientId, ioContext, readCallback));
        }

        void TcpConnection::startWrite(const boost::asio::mutable_buffers_1 & buffer)
        {
            boost::asio::async_write(this->_socket, buffer,
                boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                boost::asio::placeholders::error));
        }

        void TcpConnection::startRead(void)
        {
            auto buffer = boost::asio::buffer(_buffer, sizeof(communication_t));

            _socket.async_read_some(buffer,
                boost::bind(&TcpConnection::handleRead, shared_from_this(),
                boost::asio::placeholders::error));
        }

        void TcpConnection::handleWrite(
            const boost::system::error_code& error) const
        {
            if (error)
                std::cerr << error.message();
        }

        void TcpConnection::handleRead(
            const boost::system::error_code& error)
        {
            communication_t message;
            protocol_t data;

            memset(&message, 0, sizeof(communication_t));
            if (!error) {
                std::memcpy(&message, _buffer, sizeof(communication_t));
                _readCallback(message.protocol, std::string(message.string));

                startRead();
            } else {
                data.opcode = 13;
                data.clientId = _id;
                _readCallback(data, std::string(""));
                _socket.close();
            }
        }

        boost::asio::ip::tcp::socket & TcpConnection::getSocket(void)
        {
            return _socket;
        }

        const size_t & TcpConnection::getId(void) const
        {
            return _id;
        }
    }
}
