/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** GameThread
*/

#include "GameThread.hpp"
#include "Game.hpp"
namespace rtype {
    namespace server {
        GameThread::GameThread(const unsigned int &port, size_t & idClientCounter, const int & nbPlayers) :
            _idClientCounter(idClientCounter), _nbPlayers(nbPlayers)
        {
            _network = new network::ServerNetwork(port, _idClientCounter, [this](const protocol_t &data, const std::string &string) {
                this->readNetworkCallback(data, string);
            }, [this](const network::TcpConnection::pointer &connection, const size_t & clientId){
                this->acceptNetworkCallback(connection, clientId);
            });
            _sceneManager = new engine::SceneManager(_network, engine::SceneManager::SERVER);

            _inputHandler = new InputHandler(*this);

            _opFuncList.insert(std::make_pair(13, &GameThread::opDisconnect));
            _opFuncList.insert(std::make_pair(110, &GameThread::opInput));

            _startTime = std::chrono::steady_clock::now();
            _currentTime = std::chrono::steady_clock::now();
        }

        GameThread::~GameThread()
        {
            delete(_network);
        }

        void GameThread::mainLoop(void)
        {
            float elapsedTime = 0;
            bool playersLeft = true;
            std::vector<std::shared_ptr<engine::IObject>> vec;

            while (static_cast<int>(_network->getUdpConnection()->getClientEndpoints().size()) != _nbPlayers)
                _network->poll();

            _sceneManager->addScene(std::make_shared<Game>("game", *_sceneManager));

            while (playersLeft) {
                _network->poll();
                _currentTime = std::chrono::steady_clock::now();
                elapsedTime = static_cast<float>(
                    static_cast<float>(
                        std::chrono::duration_cast<std::chrono::microseconds>(_currentTime - _startTime).count()) / 1000000);
                _sceneManager->update(elapsedTime);
                vec = _sceneManager->getAllObjectsOfScene("game");
                playersLeft = false;
                for (auto &i : vec) {
                    if (i->getName() == "player")
                        playersLeft = true;
                }
            }
            this->endGame();
        }

        void GameThread::endGame(void)
        {
            protocol_t data;

            EMPTY_PROTOCOL(data);
            data.opcode = 32;
            _network->sendUDPPacket(data, _network->getUdpConnection());
        }

        void GameThread::acceptNetworkCallback(const network::TcpConnection::pointer &connection, const size_t & clientId)
        {
            protocol_t data;
            EMPTY_PROTOCOL(data);

            data.opcode = 1;
            data.clientId = clientId;
            _network->sendTCPPacket(data, connection);
        }

        void GameThread::readNetworkCallback(const protocol_t &data, const std::string &string)
        {
            auto opFunc = _opFuncList[data.opcode];

            if (!opFunc)
                return;
            (this->*opFunc)(data, string);
        }

        void GameThread::opDisconnect(const protocol_t & data, const std::string & text)
        {
            _network->removeTcpConnection(data.clientId);
            static_cast<void>(text);
        }

        void GameThread::opInput(const protocol_t & data, const std::string & text)
        {
            _inputHandler->inputHandle(data);
            static_cast<void>(text);
        }

        engine::ISceneManager * GameThread::getSceneManager() const
        {
            return _sceneManager;
        }

        network::ServerNetwork * GameThread::getNetwork() const
        {
            return _network;
        }
    }
}