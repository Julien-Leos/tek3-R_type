/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** InputHandler
*/

#ifndef INPUTHANDLER_HPP_
#define INPUTHANDLER_HPP_

#include "includes.hpp"
#include "Parser.hpp"
#include "Communication.hpp"
#include "IObject.hpp"

namespace rtype {
namespace server {
    class GameThread;

    class InputHandler {
        public:
            InputHandler(const GameThread & gameThread);
            virtual ~InputHandler() = default;

            void    inputHandle(const protocol_t & data);

            void    directionHandle(const protocol_t & data, std::shared_ptr<engine::IObject> playerSpaceship);
            void    shootHandle(const protocol_t & data, std::shared_ptr<engine::IObject> playerSpaceship);

        private:
            const GameThread &                      _gameThread;

            std::map<std::string, std::string>      _gameConfig;

            std::chrono::steady_clock::time_point   _shootTime;
            std::chrono::steady_clock::time_point   _releaseShootTime;

            std::map<int, std::pair<char, int>>     _directionBind = {
                {1, {'x', -1}},
                {2, {'x', 1}},
                {4, {'y', -1}},
                {8, {'y', 1}}
            };
    };
}
}

#endif /* !INPUTHANDLER_HPP_ */
