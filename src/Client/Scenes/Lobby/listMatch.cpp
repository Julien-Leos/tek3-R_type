//
// Created by simon on 27/11/19.
//

#include "listPlayers.hpp"
#include "room.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "listMatch.hpp"
#include "lobby.hpp"

namespace rtype {
    namespace client {
        void ListRoom::display(sf::RenderWindow &window)
        {
            int idx = 0;
            int pos = 0;

            for (auto &e : _elements) {
                if (idx >= _interval.first && idx <= _interval.second) {
                    e->getButton()->getComponent<engine::MovementComponent>()->setPosition(1600/2-140, 200 + (100 * pos));
                    e->getText()->getSfmlText()->setPosition(1600/2-135 + 10, 200 + (100 * pos) + 5);
                    e->display(window);
                    pos++;
                }
                idx++;
            }
        }

        ListRoom::ListRoom(const std::string &name, rtype::engine::ISceneManager &sceneManager,
                           std::vector<std::string> &listRooms, std::pair<int, int> interval) : Scene(name, sceneManager), _interval(interval)
        {
            static_cast<void>(listRooms);
        }

        void ListRoom::setInterval(const std::pair<int, int> &interval)
        {
            _interval = interval;
        }

        const std::pair<int, int> &ListRoom::getInterval() const
        {
            return _interval;
        }

        void ListRoom::manageEvents(const rtype::engine::event_t &event)
        {
            for (auto &e : _elements) {
                e->manageEvents(event);
            }
        }

        void ListRoom::addRoom(std::string &name, unsigned int id)
        {
            if (!_elements.empty())
                for (auto &e : _elements) {
                    if (e) {
                        if (e->getName() == std::string("room_" + name)) {
                            return;
                        }
                    }
                }
            std::shared_ptr<Room> room = std::make_shared<Room>(
                    "room_" + name,
                    19,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("enteringRoom");
                        protocol_t data;
                        EMPTY_PROTOCOL(data);
                        data.opcode = 22;
                        data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                        data.data = std::static_pointer_cast<Room>(button.getScene().getObject(button.getName()))->getIdRoom();
                        const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                        button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection);
                    },
                    [](engine::Button &button) {
                        static_cast<void>(button);
                    },
                    [](engine::Button &button) {
                        static_cast<void>(button);
                    },
                    *this,
                    pos_t({0,0}), name, id
            );
            std::function<void(engine::Button &)> callback = [](engine::Button &button) {
                if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                    button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(20);
            };
            std::function<void(engine::Button &)> callbackUnHover = [](engine::Button &button) {
                if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                    button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(19);
            };
            room->getButton()->setCallbackHover(callback);
            room->getButton()->setCallbackUnHover(callbackUnHover);
            this->addObject(room);
            _elements.emplace_back(room);
        }

        void ListRoom::removeRoom(unsigned int id)
        {
            int pos = 0;

            for (auto &e : _elements) {
                if (e) {
                    if (e->getIdRoom() == id) {
                        _elements.erase(_elements.begin() + pos);
                        return;
                    }
                }
                pos++;
            }
        }

        std::vector<std::shared_ptr<Room>> &ListRoom::getElements()
        {
            return _elements;
        }

        Room::Room(const std::string &name, const unsigned &spriteId,
                   std::function<void(engine::Button &)> callbackPressed,
                   std::function<void(engine::Button &)> callbackHover,
                   std::function<void(engine::Button &)> callbackUnHover,
                   rtype::engine::IScene & scene,
                   const pos_t &position,
                   const std::string &roomName, unsigned int id) : Object(name, spriteId, scene, position), _name(roomName), _isHover(false), _id(id)
        {
            std::shared_ptr<rtype::engine::Button> button = std::make_shared<rtype::engine::Button>(
                    "room_" + roomName,
                    19,
                    callbackPressed,
                    callbackHover,
                    callbackUnHover,
                    scene,
                    position
            );
            button->getComponent<engine::MovementComponent>()->setPosition(position.x, position.y);
            std::shared_ptr<rtype::engine::Text> title = std::make_shared<rtype::engine::Text>(
                    "room_" + roomName,
                    roomName,
                    50,
                    sf::Color(sf::Color::White),
                    scene,
                    position
            );
            title->getComponent<engine::MovementComponent>()->setPosition(position.x, position.y);
            _button = button;
            _text = title;
        }

        void Room::display(sf::RenderWindow &window)
        {
            _button->display(window);
            _text->display(window);
        }

        std::shared_ptr<rtype::engine::Button> Room::getButton()
        {
            return _button;
        }

        std::shared_ptr<rtype::engine::Text> Room::getText()
        {
            return _text;
        }

        void Room::manageEvents(const rtype::engine::event_t &event)
        {
            sf::Vector2f mousePos = {event.mousePosition.first, event.mousePosition.second};

            if (_button->getComponent<rtype::engine::AnimationComponent>()->getSprite().getGlobalBounds().contains(mousePos)) {
                if (!_isHover) {
                    _button->callHover();
                }
                _isHover = true;
            } else {
                if (_isHover) {
                    _button->callUnHover();
                }
                _isHover = false;
            }
            if (event.mouseButtonPressed.find(engine::MouseLeft)->second) {
                if (_button->getComponent<engine::AnimationComponent>()->getSprite().getGlobalBounds().contains(mousePos))
                    _button->callPressed();
            }
        }

        unsigned int Room::getIdRoom() const
        {
            return _id;
        }

        void Room::setId(unsigned int id)
        {
            _id = id;
        }
    }
}