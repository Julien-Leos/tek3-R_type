/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component
*/

#include "Component.hpp"

namespace rtype {
    namespace engine {

Component::Component(IObject &owner)
: _owner(owner)
{
}

void Component::update(const float &delta)
{
    static_cast<void>(delta);
}

void Component::activate()
{
    _isActivated = true;
}

void Component::disable()
{
    _isActivated = false;
}

bool Component::isActivated() const
{
    return _isActivated;
}
}
}
