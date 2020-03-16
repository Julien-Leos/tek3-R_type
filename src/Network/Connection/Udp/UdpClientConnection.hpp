/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** UdpClientConnection
*/

#ifndef UDPCLIENTCONNECTION_HPP_
#define UDPCLIENTCONNECTION_HPP_

#include "includes.hpp"
#include "Communication.hpp"

namespace rtype {
    namespace network {
        /**
         * @brief Handle the UDP packets. It must manage the receiving and
         * sending of these
         * 
         */
        class UdpClientConnection : public boost::enable_shared_from_this<UdpClientConnection> {
            public:
                /**
                 * @brief Needed to keep in the memory the recently created
                 * connection. Without this pointer, connections would be lost
                 * because of the dyssynchrony of the Network 
                 * 
                 */
                typedef boost::shared_ptr<UdpClientConnection> pointer;

                /**
                 * @brief Destroy the Udp Connection object
                 * 
                 */
                ~UdpClientConnection();

                /**
                 * @brief Just create a new UdpClientConnection class in a pointer and
                 * returns it
                 * 
                 * @param ioContext Context of the socket
                 * @param endpoint Endpoint of the socket
                 * @param readCallback Callback called when receiving a new
                 * packet
                 * @return pointer 
                 */
                static pointer create(
                    boost::asio::io_context& ioContext,
                    boost::asio::ip::udp::endpoint endpoint,
                    std::function<void(const protocol_t &, const std::string &)> readCallback);

                /**
                 * @brief Prepare the Connection to send a new packet
                 * 
                 * @param buffer Contains the packet's data
                 */
                void startSend(const boost::asio::mutable_buffers_1 & buffer);

                /**
                 * @brief Prepare the Connection to receive a packet
                 * 
                 */
                void startReceive(void);

                /**
                 * @brief Triggered when a new packets has been sent
                 * 
                 * @param error Encountered errors
                 */
                void handleSend(const boost::system::error_code& error) const;

                /**
                 * @brief Triggered when a new packets has been received
                 * 
                 * @param error Encountered errors
                 */
                void handleReceive(const boost::system::error_code& error);

                /**
                 * @brief Get the Socket object
                 * 
                 * @return boost::asio::ip::udp::socket& 
                 */
                boost::asio::ip::udp::socket& getSocket(void);

            private:
                /**
                 * @brief Construct a new Udp Connection object
                 * 
                 * @param ioContext Context of the socket
                 * @param endpoint Endpoint of the socket
                 * @param readCallback Callback called when receiving a new
                 * packet
                 */
                UdpClientConnection(
                    boost::asio::io_context& ioContext,
                    boost::asio::ip::udp::endpoint endpoint,
                    std::function<void(const protocol_t &, const std::string &)> readCallback);


                boost::asio::ip::udp::socket    _socket;
                boost::asio::ip::udp::endpoint  _emptyEndpoint;
                boost::asio::ip::udp::endpoint  _fillEndpoint;
                char                            _buffer[sizeof(protocol_t) + MESSAGE_SIZE];

                std::function<void(const protocol_t &, const std::string &)>  _readCallback;
        };
    }
}

#endif /* !UDPCLIENTCONNECTION_HPP_ */
