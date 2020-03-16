//
// Created by simon on 30/11/19.
//

#include "listPlayers.hpp"

namespace rtype {
    namespace client {

        Player::Player(const std::string &name, const unsigned &spriteId,
                       std::function<void(engine::Button &)> callbackPressed,
                       std::function<void(engine::Button &)> callbackHover,
                       std::function<void(engine::Button &)> callbackUnHover, rtype::engine::IScene &scene,
                       const pos_t &position, const std::string &username, const unsigned &id) : Object(name, spriteId, scene, position), _name(username), _isHover(false), _id(id)
        {
            std::shared_ptr<rtype::engine::Button> button = std::make_shared<rtype::engine::Button>(
                    username,
                    19,
                    callbackPressed,
                    callbackHover,
                    callbackUnHover,
                    scene,
                    position
            );
            button->getComponent<engine::MovementComponent>()->setPosition(position.x, position.y);
            std::shared_ptr<rtype::engine::Text> title = std::make_shared<rtype::engine::Text>(
                    "player_" + username,
                    username,
                    50,
                    sf::Color(sf::Color::White),
                    scene,
                    position
            );
            title->getComponent<engine::MovementComponent>()->setPosition(position.x, position.y);
            _button = button;
            _text = title;
        }

        void rtype::client::Player::display(sf::RenderWindow &window)
        {
            _button->display(window);
            _text->display(window);
        }

        void rtype::client::Player::manageEvents(const rtype::engine::event_t &event)
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

        std::shared_ptr<rtype::engine::Button> rtype::client::Player::getButton()
        {
            return _button;
        }

        std::shared_ptr<rtype::engine::Text> rtype::client::Player::getText()
        {
            return _text;
        }

        unsigned int rtype::client::Player::getIdPlayer() const
        {
            return _id;
        }

        void rtype::client::Player::setId(unsigned int id)
        {
            _id = id;
        }

        rtype::client::ListPlayers::ListPlayers(const std::string &name, rtype::engine::ISceneManager &sceneManager,
                                                std::vector<std::string> &listPlayers, std::pair<int, int> interval) : Scene(name, sceneManager), _interval(interval)
        {
            static_cast<void>(listPlayers);
        }

        void rtype::client::ListPlayers::display(sf::RenderWindow &window)
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

        void rtype::client::ListPlayers::manageEvents(const rtype::engine::event_t &event)
        {
            for (auto &e : _elements)
                e->manageEvents(event);
        }

        void rtype::client::ListPlayers::setInterval(const std::pair<int, int> &interval)
        {
            _interval = interval;

        }

        const std::pair<int, int> &rtype::client::ListPlayers::getInterval() const
        {
            return _interval;
        }

        void rtype::client::ListPlayers::addPlayer(std::string &name, const unsigned int &id)
        {
            std::shared_ptr<rtype::client::Player> player = std::make_shared<rtype::client::Player>(
                    "player_" + name,
                    29,
                    [](engine::Button &button){
                        static_cast<void>(button);
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
            this->addObject(player);
            _elements.push_back(player);
        }

        void rtype::client::ListPlayers::removePlayer(const unsigned int &id)
        {
            int pos = 0;

            for (auto &e : _elements) {
                if (e) {
                    if (e->getIdPlayer() == id) {
                        _elements.erase(_elements.begin() + pos);
                        return;
                    }
                }
                pos++;
            }
        }

        void rtype::client::ListPlayers::addPlayerReady(const unsigned int &id)
        {
            int pos = 0;

            for (auto &e : _elements) {
                if (e) {
                    if (e->getIdPlayer() == id) {
                        e->getButton()->getComponent<rtype::engine::AnimationComponent>()->changeSprite(30);
                        return;
                    }
                }
                pos++;
            }
        }


        std::vector<std::shared_ptr<rtype::client::Player>> &rtype::client::ListPlayers::getElements()
        {
            return _elements;
        }

    }
}