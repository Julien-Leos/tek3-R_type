/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Object
*/

#include "Object.hpp"

namespace rtype {
    namespace engine {
Object::Object(const std::string &name, const unsigned &spriteId, IScene &scene, const pos_t &position)
: _name(name), _scene(scene), _hidden(false), _objectId(scene.getSceneManager().getNewObjectId())
{
    addComponent(std::make_shared<MovementComponent>(*this));
    getComponent<MovementComponent>()->setPosition(position.x, position.y);
    addComponent(std::make_shared<AnimationComponent>(*this, spriteId));
    getComponent<AnimationComponent>()->getSprite().setPosition(position.x, position.y);
}

rtype::engine::Object::Object(const std::string &name, const unsigned &spriteId, const unsigned &objectId, IScene &scene, const pos_t &position)
: _name(name), _scene(scene), _hidden(false), _objectId(objectId)
{
    addComponent(std::make_shared<MovementComponent>(*this));
    getComponent<MovementComponent>()->setPosition(position.x, position.y);
    addComponent(std::make_shared<AnimationComponent>(*this, spriteId));
    getComponent<AnimationComponent>()->getSprite().setPosition(position.x, position.y);
}

rtype::engine::Object::~Object()
{
}

void Object::display(sf::RenderWindow &window)
{
    if (this->isHidden())
        return;

    sf::Sprite sprite = getComponent<AnimationComponent>()->getSprite();
    const pos_t pos = getComponent<MovementComponent>()->getPosition();

    getComponent<AnimationComponent>()->getSprite().setPosition(pos.x, pos.y);
    window.draw(sprite);
}

float Object::update(const float &actualTime)
{
    float delta = 0;

    if (actualTime < _oldTime || _oldTime == 0)
        _oldTime = actualTime;
    delta = actualTime - _oldTime;
    for (auto &i: _components)
        if (i.second && i.second->isActivated())
            i.second->update(delta);
    _oldTime = actualTime;
    return delta;
}

void Object::manageEvents(const event_t &event)
{
    static_cast<void>(event);
}

void Object::collide(std::shared_ptr<IObject> other)
{
    static_cast<void>(other);
}

const std::string &Object::getName() const
{
    return _name;
}

const unsigned &Object::getId() const
{
    return _objectId;
}

void Object::eventHit(std::shared_ptr<IObject> other)
{
    static_cast<void>(other);
}

void Object::eventReachedDestination()
{
}

IScene & Object::getScene() const
{
    return _scene;
}

bool Object::isHidden() const
{
    return _hidden;
}

void Object::setHidden(bool hidden)
{
    _hidden = hidden;
}
}
}