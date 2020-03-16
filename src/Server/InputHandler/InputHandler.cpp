/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** InputHandler
*/

#include "InputHandler.hpp"
#include "GameThread.hpp"
#include "MovementComponent.hpp"
#include "LauncherComponent.hpp"

namespace rtype {
namespace server {
    InputHandler::InputHandler(const GameThread & gameThread) : _gameThread(gameThread)
    {
        _gameConfig = engine::Parser::getConfigFile("game");
    }

    void    InputHandler::inputHandle(const protocol_t & data)
    {
        auto playerSpaceship = _gameThread.getSceneManager()->getScene("game")->getObject(data.clientId);

        if (!playerSpaceship)
            return;
        if (data.data <= 15)
            directionHandle(data, playerSpaceship);
        else
            shootHandle(data, playerSpaceship);
    }

    void    InputHandler::directionHandle(const protocol_t & data, std::shared_ptr<engine::IObject> playerSpaceship)
    {
        int directionId = data.data;
        std::vector<int> directionIdComposition;
        pos_t direction = {0, 0};
        int sprite = data.object.type;

        for (int n = 3; n >= 0; n--) {
            int power2 = pow(2, n);
            if (directionId >= power2) {
                directionIdComposition.push_back(power2);
                directionId -= power2;
            }
        }
        for (const int &comp : directionIdComposition) {
            if (_directionBind.find(comp)->second.first == 'x')
                direction.x = _directionBind.find(comp)->second.second;
            else if (_directionBind.find(comp)->second.first == 'y')
                direction.y = _directionBind.find(comp)->second.second;
        }
        sprite = direction.y == 1 ? sprite - 1 : direction.y == -1 ? sprite + 1 : sprite;
        direction.x *= std::stoi(_gameConfig.find("spaceshipSpeed")->second);
        direction.y *= std::stoi(_gameConfig.find("spaceshipSpeed")->second);
        playerSpaceship->getComponent<engine::MovementComponent>()->setSpeed(direction.x, direction.y);

        protocol_t packet;
        EMPTY_PROTOCOL(packet);
        packet.opcode = 102;
        packet.data = playerSpaceship->getId();
        packet.object.type = sprite;
        packet.object.pos = playerSpaceship->getComponent<engine::MovementComponent>()->getPosition();;
        packet.object.velocity = direction;
        _gameThread.getNetwork()->sendUDPPacket(packet, _gameThread.getNetwork()->getUdpConnection());
    }

    void    InputHandler::shootHandle(const protocol_t & data, std::shared_ptr<engine::IObject> playerSpaceship)
    {
        float elapsedTime = 0;

        if (data.data == 16) {
            _shootTime = std::chrono::steady_clock::now();
        } else if (data.data == 17) {
            _releaseShootTime = std::chrono::steady_clock::now();
            elapsedTime = static_cast<float>(
                static_cast<float>(
                    std::chrono::duration_cast<std::chrono::microseconds>(_releaseShootTime - _shootTime).count()) / 1000);

            if (elapsedTime < std::stoi(_gameConfig.find("maxShootLoadInSec")->second) * 1000) {
                auto bulletSpeed = std::stoi(_gameConfig.find("bulletSpeed")->second);
                playerSpaceship->getComponent<game::LauncherComponent>()->fireBullet(std::make_pair(bulletSpeed, 0));
            } else {
                auto rocketSpeed = std::stoi(_gameConfig.find("rocketSpeed")->second);
                playerSpaceship->getComponent<game::LauncherComponent>()->fireRocket(std::make_pair(rocketSpeed, 0));
            }
        }
    }
}
}