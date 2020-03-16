/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Bullet
*/

#include "Bullet.hpp"

namespace rtype {
namespace game {

Bullet::Bullet(engine::IScene &scene, std::shared_ptr<engine::IObject> owner, const std::pair<float, float> &speed, const pos_t &pos)
: Object("bullet", 24, scene, pos), _owner(owner)
{
    auto movement = getComponent<engine::MovementComponent>();
    auto animation = getComponent<engine::AnimationComponent>();

    movement->setPosition(pos.x, pos.y);
    movement->setFreeMoving(true);
    movement->setSpeed(speed.first, speed.second);
}

void Bullet::eventHit(std::shared_ptr<IObject> collideObject)
{
    protocol_t protocol;
    auto network = dynamic_cast<network::ServerNetwork *>(_scene.getSceneManager().getNetwork());

    if (!_scene.getObject(_owner->getId())) {
        EMPTY_PROTOCOL(protocol);
        protocol.opcode = 103;

        protocol.data = getId();
        _scene.removeObject(getId());
        network->sendUDPPacket(protocol, network->getUdpConnection());
        return;
    }
    if ((_owner->getName() == "player" && collideObject->getName().substr(0, 2) == "ai")
    || (_owner->getName().substr(0, 2) == "ai" && collideObject->getName() == "player")) {
        EMPTY_PROTOCOL(protocol);
        if (_owner->getName() == "player") {
            _owner->getComponent<engine::ScoreComponent>()->addScore(10);
            protocol.opcode = 111;
            protocol.clientId = _owner->getId();
            protocol.data = _owner->getComponent<engine::ScoreComponent>()->getScore();
            network->sendUDPPacket(protocol, network->getUdpConnection());
        } else if (collideObject->getName() == "player") {
            collideObject->getComponent<engine::HealthComponent>()->removeHealth();
            protocol.opcode = 121;
            protocol.clientId = collideObject->getId();
            protocol.data = collideObject->getComponent<engine::HealthComponent>()->getHealth();
            network->sendUDPPacket(protocol, network->getUdpConnection());
        }
        EMPTY_PROTOCOL(protocol);
        protocol.opcode = 103;

        protocol.data = getId();
        _scene.removeObject(getId());
        network->sendUDPPacket(protocol, network->getUdpConnection());

        if (collideObject->getName().substr(0, 2) == "ai"
        || (collideObject->getName() == "player"
        && collideObject->getComponent<engine::HealthComponent>()->getHealth() == 0)) {
            protocol.data = collideObject->getId();
            _scene.removeObject(collideObject->getId());
            network->sendUDPPacket(protocol, network->getUdpConnection());
            if (collideObject->getName().substr(0, 2) == "ai")
                std::static_pointer_cast<Map>(_scene.getObject("map"))->addAMobKilled();
        }
    }
}

float Bullet::update(const float &actualTime)
{
    float delta = Object::update(actualTime);
    auto network = dynamic_cast<network::ServerNetwork *>(_scene.getSceneManager().getNetwork());
    protocol_t protocol;

    if (getComponent<engine::MovementComponent>()->getPosition().x < -100
    || getComponent<engine::MovementComponent>()->getPosition().x > WINDOW_WIDTH + 50
    || getComponent<engine::MovementComponent>()->getPosition().y < -20
    || getComponent<engine::MovementComponent>()->getPosition().y > WINDOW_HEIGHT + 50) {
        _scene.removeObject(getId());
        EMPTY_PROTOCOL(protocol);
        protocol.opcode = 103;
        protocol.data = getId();
        network->sendUDPPacket(protocol, network->getUdpConnection());
    }
    return delta;
}

void Bullet::display(sf::RenderWindow &window)
{
    auto animation = getComponent<engine::AnimationComponent>();
    auto movement = getComponent<engine::MovementComponent>();

    window.draw(animation->getSprite());
}

}
}