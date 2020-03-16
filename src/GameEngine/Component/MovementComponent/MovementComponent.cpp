/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementComponent
*/

#include "MovementComponent.hpp"

namespace rtype {
    namespace engine {
MovementComponent::MovementComponent(IObject &object)
: Component(object)
{
}

bool MovementComponent::willColide(const float &delta, std::shared_ptr<IObject> other) const
{
    if (!other)
        EXCEPTION(std::runtime_error, "Parent or Other are null.");
    if (_owner.getId() == other->getId())
        return false;

    const std::pair<float, float> size = _owner.getComponent<AnimationComponent>()->getSize();
    const sf::FloatRect globalBounds = {
            _position.x + _speed.first * delta,
            _position.y + _speed.second * delta,
            size.first,
            size.second
    };
    const sf::FloatRect globalBoundsOther = {
            other->getComponent<MovementComponent>()->getPosition().x,
            other->getComponent<MovementComponent>()->getPosition().y,
            other->getComponent<AnimationComponent>()->getSize().first,
            other->getComponent<AnimationComponent>()->getSize().second
    };

    return globalBounds.intersects(globalBoundsOther);
}

void MovementComponent::update(const float &delta)
{
    bool collide = false;
    std::vector<std::shared_ptr<IObject> > objects = _owner.getScene().getObjects();

    if (!isMoving())
        return;
    for (auto &i: objects) {
        if (willColide(delta, i)) {
            if (i->getComponent<MovementComponent>()->isBlocking() && _blocking)
                collide = true;
            _owner.eventHit(i);
        }
    }
    if (!collide)
        setPosition(_position.x + _speed.first * delta, _position.y + _speed.second * delta);
    if (!_freeMoving)
        if (hasReachDuration(delta)) {
            setSpeed(0, 0);
            _owner.eventReachedDestination();
        }
}

bool MovementComponent::hasReachDuration(const float &delta)
{
    _remainingTimeMoving -= delta;
    if (_remainingTimeMoving <= 0)  {
        _remainingTimeMoving = 0;
        _position = {_destination.first, _destination.second};
        return true;
    }
    return false;
}

void MovementComponent::setSpeed(const float &x, const float &y)
{
    _speed.first = x;
    _speed.second = y;
}

void MovementComponent::setPosition(const float &x, const float &y)
{
    _position.x = x;
    _position.y = y;
}

bool MovementComponent::isMoving() const
{
    return (_speed.first != 0 || _speed.second != 0);
}

bool MovementComponent::isFreeMoving() const
{
    return _freeMoving;
}

bool MovementComponent::isBlocking() const
{
    return _blocking;
}

void MovementComponent::setFreeMoving(const bool &state)
{
    _freeMoving = state;
}

void MovementComponent::setBlocking(const bool &state)
{
    _blocking = state;
}

void MovementComponent::setDestination(const std::pair<float, float> &newDest, const float &timeToReach)
{
    _remainingTimeMoving = timeToReach;
    _speed.first = (newDest.first - _position.x) / timeToReach;
    _speed.second = (newDest.second - _position.y) / timeToReach;
    _destination.first = newDest.first;
    _destination.second = newDest.second;
    _freeMoving = false;
}

const pos_t &MovementComponent::getPosition() const
{
    return _position;
}

const std::pair<float, float> &MovementComponent::getSpeed() const
{
    return _speed;
}

const std::pair<float, float> &MovementComponent::getDestination() const
{
    return _destination;
}
    }
}