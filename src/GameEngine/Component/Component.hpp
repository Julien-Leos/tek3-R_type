/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "IComponent.hpp"

namespace rtype {
    namespace engine {
    class Component : public IComponent {
        public:
            Component(IObject &owner);
            virtual ~Component() = default;

            virtual void update(const float &delta) override;
            virtual void activate() override;
            virtual void disable() override;
            virtual bool isActivated() const override;

        protected:
            bool _isActivated = true;
            IObject &_owner;
    };
}
}

#endif /* !COMPONENT_HPP_ */
