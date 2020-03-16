/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <SFML/Window.hpp>
#include "Event.hpp"
#include "Communication.hpp"
#include "Parser.hpp"
#include "SceneManager.hpp"
#include "Network.hpp"

namespace rtype {
    namespace graphics {
        class Display;
    }

    namespace client {
        class EventHandler {
            public:
                EventHandler(const graphics::Display & display);
                virtual ~EventHandler() = default;

                void    initEvent(void);
                void    handleEvent(void);
                void    manageEvent(void);

                void    sendNewDirectionPacket(pos_t & newDirection, std::shared_ptr<rtype::engine::IObject> spaceship);
                void    sendShootPacket(std::shared_ptr<rtype::engine::IObject> spaceship);
                void    sendReleaseShootPacket(std::shared_ptr<rtype::engine::IObject> spaceship);

            private:
                const graphics::Display &   _display;

                rtype::engine::ISceneManager *  _sceneManager;
                sf::RenderWindow                _window;

                network::ClientNetwork *        _network;

                sf::Event                   _event;
                engine::event_t             _customEvent;

                std::map<std::string, std::string>  _inputConfig;
                std::map<std::string, std::string>  _gameConfig;

                pos_t                                       _direction;
                std::map<char, std::map<int, std::string>>  _directionBind = {
                    {'x', {{-1, "left"}, {1, "right"}}},
                    {'y', {{-1, "up"}, {1, "down"}}}
                };
        };
    }
}

#endif /* !EVENTHANDLER_HPP_ */
