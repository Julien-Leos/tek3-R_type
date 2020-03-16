/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** HealthComponent
*/

#ifndef HEALTHCOMPONENT_HPP_
#define HEALTHCOMPONENT_HPP_

#include "Component.hpp"
#include "IObject.hpp"
#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"

namespace rtype {
namespace engine {
    class HealthComponent : public engine::Component {
        public:
            HealthComponent(engine::IObject &parent);
            ~HealthComponent() = default;

            const size_t &getHealth() const;
            void setHealth(const size_t &health);
            void removeHealth();
            void addHealth();
        
        private:
            size_t _health = 3;

    };
}
}

#endif /* !HEALTHCOMPONENT_HPP_ */
