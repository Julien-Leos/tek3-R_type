/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "Object.hpp"
#include "IScene.hpp"
#include "MovementComponent.hpp"
#include "HealthComponent.hpp"
#include "ScoreComponent.hpp"
#include "IDisplay.hpp"
#include "ServerNetwork.hpp"
#include "Map.hpp"

namespace rtype {
namespace game {
    class Bullet : public engine::Object {
        public:
            Bullet(engine::IScene &scene, std::shared_ptr<IObject> owner, const std::pair<float, float> &speed, const pos_t &pos = {0, 0});
            ~Bullet() = default;

            void display(sf::RenderWindow &window) override;
            float update(const float &actualTime) override;

            void eventHit(std::shared_ptr<IObject> other) override;

        private:
            std::shared_ptr<engine::IObject> _owner;
    };
}
}

#endif /* !BULLET_HPP_ */
