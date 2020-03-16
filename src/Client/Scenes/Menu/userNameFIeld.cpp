//
// Created by simon on 29/11/19.
//

#include "listMatch.hpp"
#include "lobby.hpp"
#include "userNameFIeld.hpp"

namespace rtype {
    namespace client {
        userNameFIeld::userNameFIeld(const std::string &name, rtype::engine::ISceneManager &sceneManager)
                : Scene(name, sceneManager)
        {
            std::shared_ptr<rtype::engine::Button> back = std::make_shared<rtype::engine::Button>(
                    "Back",
                    11,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        button.getScene().getSceneManager().getScene("usernameField")->setIsHidden(true);
                        button.getScene().getSceneManager().getScene("menu")->setIsHidden(false);
                    },
                    [](engine::Button &button) {
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(12);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(11);
                    },
                    *this,
                    pos_t({1600/3-50, 900-200})
            );
            std::shared_ptr<rtype::engine::Button> runRoomButton = std::make_shared<rtype::engine::Button>(
                    "run",
                    17,
                    [](engine::Button &button) {
                        button.getScene().getSceneManager().getSoundManager()->playSong("welcomeToTheGame");
                        if (std::static_pointer_cast<engine::Input>(button.getScene().getObject("userNameInput"))->getText().empty())
                            return;
                        std::string username = std::static_pointer_cast<engine::Input>(button.getScene().getObject("userNameInput"))->getText();
                        protocol_t data;
                        EMPTY_PROTOCOL(data);
                        data.opcode = 11;
                        data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                        const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                        button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection, username);
                    },
                    [](engine::Button &button) {
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(18);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(17);
                    },
                    *this,
                    pos_t({1600/3+300, 900-200})
            );

            _buttons.push_back(back);
            _buttons.push_back(runRoomButton);

            for (auto &e : _buttons) {
                this->addObject(e);
                e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
            }
            std::shared_ptr<engine::Text> title = std::make_shared<engine::Text>(
                    "title",
                    "Enter your username",
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-450,50})
            );
            _texts.push_back(title);
            for (auto &e : _texts) {
                this->addObject(e);
            }
            std::shared_ptr<engine::Input> input = std::make_shared<engine::Input>("userNameInput", 19, nullptr, nullptr, nullptr, *this, pos_t({1600/2-150, 900/2-40}));
            input->getComponent<engine::MovementComponent>()->setPosition(1600/2-150, 900/2-40);
            this->addObject(input);
        }
    }
}