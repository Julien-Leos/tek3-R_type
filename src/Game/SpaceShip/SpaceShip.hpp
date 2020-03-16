/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SpaceShip
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "Object.hpp"
#include "IScene.hpp"
#include "LauncherComponent.hpp"
#include "ScoreComponent.hpp"
#include "HealthComponent.hpp"

namespace rtype {
namespace game {
    class SpaceShip : public engine::Object {
        public:
            SpaceShip(const std::string &name, engine::IScene &scene, const pos_t &position = {0, 0});
            ~SpaceShip() = default;

            void eventHit(std::shared_ptr<IObject> collideObject) override;
    };
}
}
#endif /* !SPACESHIP_HPP_ */
