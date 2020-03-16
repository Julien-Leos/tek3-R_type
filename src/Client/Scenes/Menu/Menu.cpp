//
// Created by simon on 25/11/19.
//

#include "listMatch.hpp"
#include "lobby.hpp"
#include "settings.hpp"
#include "Menu.hpp"
#include "userNameFIeld.hpp"

namespace rtype {
    namespace client {
        Menu::Menu(const std::string &name, rtype::engine::ISceneManager &sceneManager) : Scene(name, sceneManager)
        {
            std::shared_ptr<rtype::engine::Button> exitButton = std::make_shared<rtype::engine::Button>(
                    "exit",
                    9,
                    [](engine::Button &button) {
                        protocol_t data;
                        EMPTY_PROTOCOL(data);
                        data.opcode = 12;
                        data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                        const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                        button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection);
                        exit(0);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(10);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(9);
                    },
                    *this,
                    pos_t({1600/2-150, 900/1-300-50})
            );
            std::shared_ptr<rtype::engine::Button> settingsButton = std::make_shared<rtype::engine::Button>(
                    "settings",
                    7,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        if (button.getScene().getSceneManager().sceneExist("settings"))
                            button.getScene().getSceneManager().getScene("settings")->setIsHidden(false);
                        else {
                            button.getScene().getSceneManager().addScene(std::make_shared<Settings>("settings", button.getScene().getSceneManager()));
                        }
                        button.getScene().getSceneManager().getScene("menu")->setIsHidden(true);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(8);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(7);
                    },
                    *this,
                    pos_t({1600/2-150, 900/1-300-150})
            );
            std::shared_ptr<rtype::engine::Button> playButton = std::make_shared<rtype::engine::Button>(
                    "play",
                    2,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        if (button.getScene().getSceneManager().sceneExist("usernameField")) {
                            if (button.getScene().getSceneManager().sceneExist("lobby")) {
                                if (std::static_pointer_cast<Lobby>(button.getScene().getSceneManager().getScene("lobby"))->isAlreadyLogged()) {
                                    button.getScene().getSceneManager().getScene("lobby")->setIsHidden(false);
                                    button.getScene().getSceneManager().getScene("listRoom")->setIsHidden(false);
                                } else {
                                    button.getScene().getSceneManager().getScene("usernameField")->setIsHidden(false);
                                }
                            } else {
                                button.getScene().getSceneManager().getScene("usernameField")->setIsHidden(false);
                            }
                        } else {
                            button.getScene().getSceneManager().addScene(std::make_shared<userNameFIeld>("usernameField", button.getScene().getSceneManager()));
                        }
                        button.getScene().getSceneManager().getScene("menu")->setIsHidden(true);
                    },
                    [](engine::Button &button) {
                        button.getComponent<engine::AnimationComponent>()->changeSprite(3);
                    },
                    [](engine::Button &button){
                        button.getComponent<engine::AnimationComponent>()->changeSprite(2);
                    },
                    *this,
                    pos_t({1600/2-150, 900/1-300-250})
            );
            std::shared_ptr<rtype::engine::Button> logOut = std::make_shared<rtype::engine::Button>(
                    "logOut",
                    25,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("logOut");
                        std::static_pointer_cast<client::Lobby>(button.getScene().getSceneManager().getScene("lobby"))->setUsername("");
                        std::static_pointer_cast<client::ListRoom>(button.getScene().getSceneManager().getScene("listRoom"))->getElements().clear();
                        button.getScene().getObject("logOut")->setHidden(true);
                        std::static_pointer_cast<engine::Input>(button.getScene().getSceneManager().getScene("usernameField")->getObject("userNameInput"))->getTextComponent().setText("");
                        protocol_t data;
                        EMPTY_PROTOCOL(data);
                        data.opcode = 12;
                        data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                        const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                        button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(26);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(25);
                    },
                    *this,
                    pos_t({10, 50})
            );
            logOut->setHidden(true);

            _buttons.push_back(settingsButton);
            _buttons.push_back(exitButton);
            _buttons.push_back(playButton);
            _buttons.push_back(logOut);
            for (auto &e : _buttons) {
                this->addObject(e);
                e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
            }

            std::shared_ptr<engine::Text> title = std::make_shared<engine::Text>(
                    "title",
                    "R-TYPE",
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-150,50})
            );
            std::shared_ptr<engine::Text> loggedName = std::make_shared<engine::Text>(
                    "loggedName",
                    "",
                    21,
                    sf::Color(sf::Color::White),
                    *this,
                    pos_t({20,20})
            );
            _texts.push_back(title);
            _texts.push_back(loggedName);
            for (auto &e : _texts)
                this->addObject(e);
        }

        Menu::~Menu()
        {

        }

        void Menu::update(const float &actualTime)
        {
            if (_isHidden)
                return;
            if (this->getSceneManager().sceneExist("lobby")) {
                if (std::static_pointer_cast<client::Lobby>(this->getSceneManager().getScene("lobby"))->isAlreadyLogged()) {
                    std::string username = std::static_pointer_cast<client::Lobby>(this->getSceneManager().getScene("lobby"))->getUsername();
                    std::static_pointer_cast<engine::Text>(this->getObject("loggedName"))->getSfmlText()->setString("logged as " + username);
                    this->getObject("logOut")->setHidden(false);
                } else {
                    std::static_pointer_cast<engine::Text>(this->getObject("loggedName"))->getSfmlText()->setString("");
                    this->getObject("logOut")->setHidden(true);
                }
            }
            for (auto &e : _objects)
                e->update(actualTime);}
    }
}
