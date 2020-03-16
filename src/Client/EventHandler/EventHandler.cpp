/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EventHandler
*/

#include "EventHandler.hpp"
#include "Display.hpp"

namespace rtype {
namespace client {
    EventHandler::EventHandler(const graphics::Display & display) : _display(display),
        _sceneManager(display.getSceneManager()),
        _network(display.getNetwork())
    {
        _customEvent.mousePosition.first = sf::Mouse::getPosition().x;
        _customEvent.mousePosition.second = sf::Mouse::getPosition().y;

        _inputConfig = engine::Parser::getConfigFile("input");
        _gameConfig = engine::Parser::getConfigFile("game");

        for (auto &i: _customEvent.keyPressed)
            i.second = false;
        _direction = {0, 0};
    }

    void    EventHandler::initEvent()
    {
        for (auto &i: _customEvent.keyPress)
            i.second = false;
        for (auto &i: _customEvent.keyRelease)
            i.second = false;
        for (auto &i: _customEvent.mouseButtonPressed)
            i.second = false;
    }

    void    EventHandler::handleEvent()
    {
        while (_display.getWindow()->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                protocol_t data;
                EMPTY_PROTOCOL(data);
                data.opcode = 12;
                data.clientId = dynamic_cast<network::ClientNetwork *>(_sceneManager->getNetwork())->getClientId();
                const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(_sceneManager->getNetwork())->getTcpConnection();
                _sceneManager->getNetwork()->sendTCPPacket(data, connection);
                _display.getWindow()->close();
            }
            if (_event.type == sf::Event::MouseMoved) {
                _customEvent.mousePosition.first = _event.mouseMove.x;
                _customEvent.mousePosition.second = _event.mouseMove.y;
            }
            if (_event.type == sf::Event::MouseButtonPressed) {
                if (_event.mouseButton.button == sf::Mouse::Left) {
                    _customEvent.mouseButtonPressed[engine::MouseButton::MouseLeft] = true;
                    _customEvent.mousePosition.first = _event.mouseButton.x;
                    _customEvent.mousePosition.second = _event.mouseButton.y;
                }
            }
            if (_event.type == sf::Event::KeyPressed) {
                _customEvent.keyPress[static_cast<engine::Key>(_event.key.code)] = true;
            }
            if (_event.type == sf::Event::KeyReleased)
                _customEvent.keyRelease[static_cast<engine::Key>(_event.key.code)] = true;
        }
        _sceneManager->eventHandler(_customEvent);
		if (_sceneManager->getScene("game"))
        	manageEvent();
        initEvent();
    }

    void    EventHandler::manageEvent()
    {
        auto spaceship = _sceneManager->getScene("game")->getObject("ownSpaceship");
        pos_t newDirection = _direction;

        if (!spaceship)
            return;

        if (_customEvent.keyPress[engine::Key::Left] && _customEvent.keyPressed[engine::Key::Left] == false) {
            _customEvent.keyPressed[engine::Key::Left] = true;
            newDirection.x += -1;
        }
        if (_customEvent.keyPress[engine::Key::Right] && _customEvent.keyPressed[engine::Key::Right] == false) {
            _customEvent.keyPressed[engine::Key::Right] = true;
            newDirection.x += 1;
        }
        if (_customEvent.keyPress[engine::Key::Up] && _customEvent.keyPressed[engine::Key::Up] == false) {
            _customEvent.keyPressed[engine::Key::Up] = true;
            newDirection.y += -1;
        }
        if (_customEvent.keyPress[engine::Key::Down] && _customEvent.keyPressed[engine::Key::Down] == false) {
            _customEvent.keyPressed[engine::Key::Down] = true;
            newDirection.y += 1;
        }

        if (_customEvent.keyRelease[engine::Key::Left]) {
            _customEvent.keyPressed[engine::Key::Left] = false;
            newDirection.x -= -1;
        }
        if (_customEvent.keyRelease[engine::Key::Right]) {
            _customEvent.keyPressed[engine::Key::Right] = false;
            newDirection.x -= 1;
        }
        if (_customEvent.keyRelease[engine::Key::Up]) {
            _customEvent.keyPressed[engine::Key::Up] = false;
            newDirection.y -= -1;
        }
        if (_customEvent.keyRelease[engine::Key::Down]) {
            _customEvent.keyPressed[engine::Key::Down] = false;
            newDirection.y -= 1;
        }
        if (newDirection.x != _direction.x || newDirection.y != _direction.y)
            sendNewDirectionPacket(newDirection, spaceship);

        if (_customEvent.keyPress[engine::Key::Space] && _customEvent.keyPressed[engine::Key::Space] == false) {
            _customEvent.keyPressed[engine::Key::Space] = true;
            sendShootPacket(spaceship);
        }
        if (_customEvent.keyRelease[engine::Key::Space]) {
            _customEvent.keyPressed[engine::Key::Space] = false;
            sendReleaseShootPacket(spaceship);
        }
    }

    void    EventHandler::sendNewDirectionPacket(pos_t & newDirection, std::shared_ptr<rtype::engine::IObject> spaceship)
    {
        int directionId = 0;
        protocol_t packet;
        EMPTY_PROTOCOL(packet);

        if (!spaceship)
            return;

        _direction = newDirection;

        newDirection.x *= std::stoi(_gameConfig.find("spaceshipSpeed")->second);
        newDirection.y *= std::stoi(_gameConfig.find("spaceshipSpeed")->second);
        spaceship->getComponent<engine::MovementComponent>()->setSpeed(newDirection.x, newDirection.y);

        try {
            if (_direction.x != 0)
                directionId += std::stoi(_inputConfig.find(_directionBind.find('x')->second.find(_direction.x)->second)->second);
            if (_direction.y != 0)
                directionId += std::stoi(_inputConfig.find(_directionBind.find('y')->second.find(_direction.y)->second)->second);
        } catch (std::exception &e) {
            return;
        }

        packet.opcode = 110;
        packet.clientId = spaceship->getId();
        packet.data = directionId;
        packet.object.type = spaceship->getComponent<engine::AnimationComponent>()->getSpriteId();
        _network->sendUDPPacket(packet, _network->getUdpConnection());
    }

    void    EventHandler::sendShootPacket(std::shared_ptr<rtype::engine::IObject> spaceship)
    {
        protocol_t packet;
        EMPTY_PROTOCOL(packet);

        packet.opcode = 110;
        packet.clientId = spaceship->getId();
        packet.data = 16;
        _network->sendUDPPacket(packet, _network->getUdpConnection());
    }

    void    EventHandler::sendReleaseShootPacket(std::shared_ptr<rtype::engine::IObject> spaceship)
    {
        protocol_t packet;
        EMPTY_PROTOCOL(packet);

        packet.opcode = 110;
        packet.clientId = spaceship->getId();
        packet.data = 17;
        _network->sendUDPPacket(packet, _network->getUdpConnection());
    }
}
}