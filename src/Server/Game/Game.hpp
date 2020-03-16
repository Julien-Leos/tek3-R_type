/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Scene.hpp"
#include "SpaceShip.hpp"
#include "Server.hpp"
#include "ServerNetwork.hpp"
#include "Communication.hpp"
#include "Map.hpp"

namespace rtype {
    namespace server {
        class Game : public engine::Scene {
            public:
                Game(const std::string &name, engine::ISceneManager &sceneManager);
                ~Game() = default;

            private:
                std::shared_ptr<game::Map> _map;
        };
    }
}

#endif /* !GAME_HPP_ */
