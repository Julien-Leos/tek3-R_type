/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../includes.hpp"
#include "../Network/Communication.hpp"

#include "ClientNetwork.hpp"
#include "Display.hpp"
#include "listMatch.hpp"
#include "lobby.hpp"
#include "room.hpp"
#include "listPlayers.hpp"
#include "Input.hpp"
#include "Protocol.hpp"

namespace rtype {
    namespace client {
        #define DEFAULT_PORT 7171

        /**
         * @brief Main Client Class. It has to handle all the foreground work of
         * the RType project.
         *
         */
        class Client {
            public:
                /**
                 * @brief Construct a new Client object
                 *
                 */
                Client();

                /**
                 * @brief Destroy the Client object
                 *
                 */
                ~Client();

                void init(void);

                void run(void);

                /**
                 * @brief Triggered when a new packet has been received on the
                 * Client
                 *
                 * @param data Data of the packet
                 * @param string Optional data string of the packet
                 */
                void readNetworkCallback(const protocol_t &data, const std::string &string);

                /**
                 * @brief ...
                 *
                 */
                void connectNetworkCallback();


                rtype::graphics::Display *              _display;
                rtype::network::ClientNetwork *         _network;

            protected:
                Protocol                                _protocol;

        };
    }
}

#endif /* !CLIENT_HPP_ */
