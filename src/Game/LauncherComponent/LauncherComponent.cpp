/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** LauncherComponent
*/

#include "LauncherComponent.hpp"
#include "ServerNetwork.hpp"

namespace rtype {
namespace game {

LauncherComponent::LauncherComponent(engine::IObject &parent)
: Component(parent)
{
}

void LauncherComponent::fireBullet(const std::pair<float, float> &speed)
{
    const pos_t pos = _owner.getComponent<engine::MovementComponent>()->getPosition();
    const std::pair<float, float> size = _owner.getComponent<engine::AnimationComponent>()->getSize();
    pos_t bulletPos = {pos.x + size.first / 2, pos.y + size.second / 2};
    auto network = dynamic_cast<network::ServerNetwork *>(_owner.getScene().getSceneManager().getNetwork());

    auto obj = _owner.getScene().addObject(std::make_shared<Bullet>(_owner.getScene(), _owner.getScene().getObject(_owner.getId()), speed, bulletPos));

    protocol_t packet;
    EMPTY_PROTOCOL(packet);
    packet.opcode = 101;
    packet.data = obj->getId();
    packet.object.type = 24;
    packet.object.pos = bulletPos;
    packet.object.velocity = {speed.first, speed.second};
    network->sendUDPPacket(packet, network->getUdpConnection());
}

void LauncherComponent::fireRocket(const std::pair<float, float> &speed)
{
    const pos_t pos = _owner.getComponent<engine::MovementComponent>()->getPosition();
    const std::pair<float, float> size = _owner.getComponent<engine::AnimationComponent>()->getSize();
    pos_t bulletPos = {pos.x + size.first / 2, pos.y + size.second / 2};

    _owner.getScene().addObject(std::make_shared<Bullet>(_owner.getScene(), _owner.getScene().getObject(_owner.getId()), speed, pos_t(bulletPos)));

    auto network = dynamic_cast<network::ServerNetwork *>(_owner.getScene().getSceneManager().getNetwork());
    protocol_t packet;
    EMPTY_PROTOCOL(packet);
    packet.opcode = 101;
    packet.data = _owner.getId();
    packet.object.type = 54;
    packet.object.pos = bulletPos;
    packet.object.velocity = {speed.first, speed.second};
    network->sendUDPPacket(packet, network->getUdpConnection());
}
}
}