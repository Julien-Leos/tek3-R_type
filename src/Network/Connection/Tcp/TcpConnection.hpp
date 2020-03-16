/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** TcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include "../../../includes.hpp"
#include "../../Communication.hpp"

namespace rtype {
    namespace network {
        /**
         * @brief Handle the TCP packets. It must manage the reading and writing
         * of these
         * 
         */
        class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
            public:
                /**
                 * @brief Needed to keep in the memory the recently created
                 * connection. Without this pointer, connections would be lost
                 * because of the dyssynchrony of the Network 
                 * 
                 */
                typedef boost::shared_ptr<TcpConnection> pointer;

                /**
                 * @brief Destroy the Tcp Connection object
                 * 
                 */
                ~TcpConnection();

                /**
                 * @brief Just create a new TcpConnection class in a pointer and
                 * returns it
                 * 
                 * @param clientId Id of the Client which is linked to the TCP
                 * connection 
                 * @param ioContext Context of the socket
                 * @param readCallback Callback called when receiving a new
                 * packet
                 * @return pointer 
                 */
                static pointer create(
                    const size_t & clientId,
                    boost::asio::io_context& ioContext,
                    std::function<void(const protocol_t &, const std::string &)> readCallback);

                /**
                 * @brief Prepare the Connection to write a new packet
                 * 
                 * @param buffer Contains the packet's data
                 */
                void startWrite(const boost::asio::mutable_buffers_1 & buffer);

                /**
                 * @brief Prepare the Connection to read a packet
                 * 
                 */
                void startRead(void);

                /**
                 * @brief Triggered when a new packets has been written
                 * 
                 * @param error Encountered errors
                 */
                void handleWrite(
                    const boost::system::error_code& error) const;

                /**
                 * @brief Triggered when a new packets has been read
                 * 
                 * @param error Encountered errors
                 */
                void handleRead(
                    const boost::system::error_code& error);

                /**
                 * @brief Get the Socket object
                 * 
                 * @return boost::asio::ip::tcp::socket& 
                 */
                boost::asio::ip::tcp::socket &  getSocket(void);

                /**
                 * @brief Get the Id object
                 * 
                 * @return const size_t& 
                 */
                const size_t &                  getId(void) const;

            private:
                /**
                 * @brief Construct a new Tcp Connection object
                 * 
                 * @param clientId Id of the Client which is linked to the TCP
                 * connection 
                 * @param ioContext Context of the socket
                 * @param readCallback Callback called when receiving a new
                 * packet
                 */
                TcpConnection(
                    const size_t & clientId,
                    boost::asio::io_context& ioContext,
                    std::function<void(const protocol_t &, const std::string &)> readCallback);


                const size_t                    _id;

                boost::asio::ip::tcp::socket    _socket;
                char                            _buffer[sizeof(protocol_t) + MESSAGE_SIZE];

                std::function<void(const protocol_t &, const std::string &)>  _readCallback;
        };
    }
}

#endif /* !TCPCONNECTION_HPP_ */
