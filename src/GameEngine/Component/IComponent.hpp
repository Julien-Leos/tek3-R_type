/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "IObject.hpp"

namespace rtype {
    namespace engine {
        class IComponent {
            public:
                virtual ~IComponent() = default;

                virtual void update(const float &delta) = 0;
                virtual void activate() = 0;
                virtual void disable() = 0;
                virtual bool isActivated() const = 0;
        };
    }
}

#endif /* !ICOMPONENT_HPP_ */
