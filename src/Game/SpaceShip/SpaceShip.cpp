/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SpaceShip
*/

#include "SpaceShip.hpp"

namespace rtype {
namespace game {

SpaceShip::SpaceShip(const std::string &name, engine::IScene &scene, const pos_t &position)
: Object(name, 22, scene, position)
{
    getComponent<engine::MovementComponent>()->setPosition(position.x, position.y);
    getComponent<engine::MovementComponent>()->setFreeMoving(true);
    addComponent<game::LauncherComponent>(std::make_shared<game::LauncherComponent>(*this));
    addComponent<engine::HealthComponent>(std::make_shared<engine::HealthComponent>(*this));
    addComponent<engine::ScoreComponent>(std::make_shared<engine::ScoreComponent>(*this));
}

void SpaceShip::eventHit(std::shared_ptr<IObject> collideObject)
{
    protocol_t protocol;
    auto network = dynamic_cast<network::ServerNetwork *>(_scene.getSceneManager().getNetwork());

    Object::eventHit(collideObject);
    EMPTY_PROTOCOL(protocol);
    if (collideObject->getName().substr(0, 2) == "ai") {
        protocol.opcode = 103; 
        protocol.data = collideObject->getId();
        _scene.removeObject(collideObject->getId());
        network->sendUDPPacket(protocol, network->getUdpConnection());
    }
}

}
}