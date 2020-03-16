/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** HealthComponent
*/

#include "HealthComponent.hpp"

namespace rtype {
namespace engine {

HealthComponent::HealthComponent(engine::IObject &parent) : Component(parent)
{
}

const size_t &HealthComponent::getHealth() const
{
    return _health;
}

void HealthComponent::setHealth(const size_t &health)
{
    _health = health;
}

void HealthComponent::removeHealth()
{
    _health--;
}

void HealthComponent::addHealth()
{
    _health++;
}

}
}
