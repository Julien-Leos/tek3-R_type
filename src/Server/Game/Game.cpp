/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game
*/

#include "Game.hpp"

namespace rtype {
    namespace server {

Game::Game(const std::string &name, engine::ISceneManager &sceneManager)
: Scene(name, sceneManager)
{
    network::ServerNetwork * network = dynamic_cast<network::ServerNetwork *>(GET_NETWORK);
    std::vector<int> spriteIds = {22, 46, 49, 52}; 
    auto ids = network->getClientsIds();
    unsigned int nbPlayers = ids.size();
    std::shared_ptr<game::SpaceShip> spaceship;
    pos_t spaceshipPos;
    protocol_t shipPacket;
    EMPTY_PROTOCOL(shipPacket);
    shipPacket.opcode = 101;
    shipPacket.object.isCollide = 1;

    for (unsigned int i = 0; i < nbPlayers; i++) {
        spaceshipPos = {50, WINDOW_HEIGHT / (static_cast<float>(nbPlayers) + 1) * (i + 1)};
        spaceship = std::make_shared<game::SpaceShip>("player", *this, spaceshipPos);
        spaceship->getComponent<engine::MovementComponent>()->setBlocking(true);
        this->addObject(spaceship);
        shipPacket.clientId = ids[i];
        shipPacket.data = spaceship->getId();
        shipPacket.object.type = spriteIds[i];
        shipPacket.object.pos = spaceshipPos;
        network->sendUDPPacket(shipPacket, network->getUdpConnection());
    }

    std::shared_ptr<game::Map> map = std::make_shared<game::Map>(*this);
    this->addObject(map);
    lua_pushlightuserdata(map->getState(), map.get());
    lua_setglobal(map->getState(), "MAP");

    pos_t wallPos1 = {0, -10};
    std::shared_ptr<engine::Object> wall1 = std::make_shared<engine::Object>("wall", 0, *this, wallPos1);
    wall1->getComponent<engine::AnimationComponent>()->setSize(WINDOW_WIDTH, 10);
    wall1->getComponent<engine::MovementComponent>()->setBlocking(true);
    this->addObject(wall1);

    pos_t wallPos2 = {-10, 0};
    std::shared_ptr<engine::Object> wall2 = std::make_shared<engine::Object>("wall", 0, *this, wallPos2);
    wall2->getComponent<engine::AnimationComponent>()->setSize(10, WINDOW_HEIGHT);
    wall2->getComponent<engine::MovementComponent>()->setBlocking(true);
    this->addObject(wall2);

    pos_t wallPos3 = {WINDOW_WIDTH, 0};
    std::shared_ptr<engine::Object> wall3 = std::make_shared<engine::Object>("wall", 0, *this, wallPos3);
    wall3->getComponent<engine::AnimationComponent>()->setSize(10, WINDOW_HEIGHT);
    wall3->getComponent<engine::MovementComponent>()->setBlocking(true);
    this->addObject(wall3);

    pos_t wallPos4 = {0, WINDOW_HEIGHT};
    std::shared_ptr<engine::Object> wall4 = std::make_shared<engine::Object>("wall", 0, *this, wallPos4);
    wall4->getComponent<engine::AnimationComponent>()->setSize(WINDOW_WIDTH, 10);
    wall4->getComponent<engine::MovementComponent>()->setBlocking(true);
    this->addObject(wall4);


    protocol_t wallPacket;
    EMPTY_PROTOCOL(wallPacket);
    wallPacket.opcode = 101;
    wallPacket.object.isCollide = 1;

    wallPacket.data = wall1->getId();
    wallPacket.object.type = 43;
    wallPacket.object.pos = wallPos1;
    network->sendUDPPacket(wallPacket, network->getUdpConnection());

    wallPacket.data = wall2->getId();
    wallPacket.object.type = 44;
    wallPacket.object.pos = wallPos2;
    network->sendUDPPacket(wallPacket, network->getUdpConnection());

    wallPacket.data = wall3->getId();
    wallPacket.object.type = 44;
    wallPacket.object.pos = wallPos3;
    network->sendUDPPacket(wallPacket, network->getUdpConnection());

    wallPacket.data = wall4->getId();
    wallPacket.object.type = 43;
    wallPacket.object.pos = wallPos4;
    network->sendUDPPacket(wallPacket, network->getUdpConnection());
}

}
}
