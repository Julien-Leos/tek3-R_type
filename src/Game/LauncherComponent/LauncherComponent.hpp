/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** LauncherComponent
*/

#ifndef LAUNCHERCOMPONENT_HPP_
#define LAUNCHERCOMPONENT_HPP_

#include "Component.hpp"
#include "IObject.hpp"
#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"
#include "Bullet.hpp"

namespace rtype {
namespace game {
    class LauncherComponent : public engine::Component {
        public:
            LauncherComponent(engine::IObject &parent);
            ~LauncherComponent() = default;

            void fireBullet(const std::pair<float, float> &speed);
            void fireRocket(const std::pair<float, float> &speed);

    };
}
}
#endif /* !LAUNCHERCOMPONENT_HPP_ */
