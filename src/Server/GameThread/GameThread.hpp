/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** GameThread
*/

#ifndef GAMETHREAD_HPP_
#define GAMETHREAD_HPP_

#include "../includes.hpp"

#include "../Network/Server/ServerNetwork.hpp"
#include "SceneManager.hpp"
#include "InputHandler.hpp"
namespace rtype {
    namespace server {
        class GameThread {
            public:
                typedef void (GameThread::*opFunc)(const protocol_t &, const std::string &);

                GameThread(const unsigned int &port, size_t & idClientCounter, const int & nbPlayers);
                ~GameThread();

                void mainLoop(void);
                void readNetworkCallback(const protocol_t &data, const std::string &string);
                void acceptNetworkCallback(const network::TcpConnection::pointer &connection, const size_t & clientId);

                engine::ISceneManager * getSceneManager() const;

                network::ServerNetwork * getNetwork() const;

                /**
                 * @brief Called when a Client is disconnected of the Server
                 *
                 * @param data Packet
                 * @param text Packet's text
                 */
                void opDisconnect(const protocol_t & data, const std::string & text);

                /**
                 * @brief Called when ...
                 *
                 * @param data Packet
                 * @param text Packet's text
                 */
                void opInput(const protocol_t & data, const std::string & text);

            private:
                /**
                 * @brief Called when ...
                 *
                 */
				void endGame(void);

                network::ServerNetwork *    _network;
                engine::SceneManager *      _sceneManager;

                InputHandler *              _inputHandler;

                std::map<const unsigned char, opFunc> _opFuncList;

                std::chrono::steady_clock::time_point   _startTime;
                std::chrono::steady_clock::time_point   _currentTime;

                size_t &                 _idClientCounter;
                const int &              _nbPlayers;
        };
    }
}

#endif /* !GAMETHREAD_HPP_ */
