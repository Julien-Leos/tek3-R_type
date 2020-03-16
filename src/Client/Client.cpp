/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** Client
*/

#include "Client.hpp"

namespace rtype {
    namespace client {
        Client::Client() : _protocol(*this)
        {
            _network = new network::ClientNetwork(DEFAULT_PORT, [this](const protocol_t &data, const std::string &string){
                this->readNetworkCallback(data, string);
            }, [this](void){
                this->connectNetworkCallback();
            });
            _display = new graphics::Display(WINDOW_WIDTH, WINDOW_HEIGHT, "R-Type", _network);
        }

        Client::~Client()
        {
        }

        void Client::init(void)
        {
            _display->init();
        }

        void Client::run(void)
        {
            _display->run();
        }

        void Client::readNetworkCallback(const protocol_t &data, const std::string &string)
        {
            _protocol.browseProtocols(data, string);
        }

        void Client::connectNetworkCallback()
        {
        }
    }
}