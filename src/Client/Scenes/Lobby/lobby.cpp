//
// Created by simon on 27/11/19.
//

#include "lobby.hpp"
#include "Menu.hpp"
#include "boxCreateRoom.hpp"
#include "listMatch.hpp"

namespace rtype {
    namespace client {
        Lobby::Lobby(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::string &username) : Scene(name,
                                                                                                                         sceneManager), _username(username)
        {
            std::shared_ptr<rtype::engine::Button> back = std::make_shared<rtype::engine::Button>(
                    "Back",
                    11,
                    [](engine::Button &button) {
                        if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom")) {
                            button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                            if (button.getScene().getSceneManager().sceneExist("menu"))
                                button.getScene().getSceneManager().getScene("menu")->setIsHidden(false);
                            else {
                                button.getScene().getSceneManager().addScene(std::make_shared<Menu>("menu", button.getScene().getSceneManager()));
                            }
                            button.getScene().getSceneManager().getScene("lobby")->setIsHidden(true);
                            button.getScene().getSceneManager().getScene("listRoom")->setIsHidden(true);
                        }
                    },
                    [](engine::Button &button) {
                        if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                            button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(12);
                    },
                    [](engine::Button &button){
                        if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                            button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(11);
                    },
                    *this,
                    pos_t({100, 150}));

            std::shared_ptr<rtype::engine::Button> createRoom = std::make_shared<rtype::engine::Button>(
                    "createRoom",
                    14,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        if (button.getScene().getSceneManager().sceneExist("createRoom"))
                            button.getScene().getSceneManager().getScene("createRoom")->setIsHidden(false);
                        else {
                            button.getScene().getSceneManager().addScene(std::make_shared<BoxCreateRoom>("createRoom", button.getScene().getSceneManager()));
                        }
                    },
                    [](engine::Button &button) {
                        if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                            button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(15);
                    },
                    [](engine::Button &button){
                        if (button.getScene().getSceneManager().sceneExistAndHidden("createRoom"))
                            button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(14);
                    },
                    *this,
                    pos_t({100, 900 - 100}));

            _buttons.push_back(back);
            _buttons.push_back(createRoom);
            for (auto &e : _buttons) {
                this->addObject(e);
                e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
            }

            std::shared_ptr<rtype::engine::Text> title = std::make_shared<rtype::engine::Text>(
                    "title",
                    "Welcome " + _username,
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-300,0}));
            //center text
            sf::FloatRect textRect = title->getSfmlText()->getLocalBounds();
            title->getSfmlText()->setOrigin(textRect.left + textRect.width/2.0f,
                                            textRect.top  + textRect.height/2.0f);
            title->getSfmlText()->setPosition(sf::Vector2f(1600/2.0f,50));

            std::shared_ptr<engine::Text> userCount = std::make_shared<engine::Text>(
                    "userCount",
                    "User connected: ",
                    21,
                    sf::Color(sf::Color::White),
                    *this,
                    pos_t({20,20})
            );
            _texts.push_back(title);
            _texts.push_back(userCount);
            for (auto &e : _texts) {
                this->addObject(e);
            }

            std::shared_ptr<rtype::engine::Object> panel = std::make_shared<rtype::engine::Object>("panel",
                                                                                                   33,
                                                                                                   *this,
                                                                                                   pos_t({1600/2-300, 900-400}));

            this->addObject(panel);
            panel->getComponent<engine::MovementComponent>()->setPosition(1600/2-300, 900-750);
        }

        Lobby::~Lobby()
        {

        }

        const std::string &Lobby::getUsername() const
        {
            return _username;
        }

        void Lobby::setUsername(const std::string &username)
        {
            if (username.empty())
            {
                _username.clear();
            }
            else
                _username = username;
        }

        bool Lobby::isAlreadyLogged()
        {
            if (_username.empty())
                return false;
            return true;
        }

        void Lobby::update(const float &actualTime)
        {
            static std::string oldUsername = _username;

            if (_isHidden)
                return;
            std::string username = std::static_pointer_cast<engine::Input>(this->getSceneManager().getScene("usernameField")->getObject("userNameInput"))->getText();
            _username = username;
            std::static_pointer_cast<engine::Text>(this->getObject("title"))->getSfmlText()->setString("Welcome " + username);
            for (auto &e : _objects)
                e->update(actualTime);
        }
    }
}