//
// Created by simon on 27/11/19.
//

#include "Input.hpp"
#include "boxCreateRoom.hpp"
#include "listMatch.hpp"


namespace rtype {
    namespace client {
        BoxCreateRoom::BoxCreateRoom(const std::string &name, rtype::engine::ISceneManager &sceneManager)
                : Scene(name, sceneManager)
        {
            std::shared_ptr<rtype::engine::Button> back = std::make_shared<rtype::engine::Button>(
                    "Back",
                    11,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        if (button.getScene().getSceneManager().sceneExist("createRoom"))
                            button.getScene().getSceneManager().getScene("createRoom")->setIsHidden(true);
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
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("roomCreated");
                        std::string roomName =  std::static_pointer_cast<rtype::engine::Input>(button.getScene().getSceneManager().getScene("createRoom")->getObject("inputBox"))->getText();
                        if (button.getScene().getSceneManager().sceneExist("listRoom")) {
                            protocol_t data;
                            EMPTY_PROTOCOL(data);
                            data.opcode = 21;
                            data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                            const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                            button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection, roomName);
                        }
                        button.getScene().getSceneManager().getScene("createRoom")->setIsHidden(true);
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


            std::shared_ptr<rtype::engine::Object> transparentBackground = std::make_shared<rtype::engine::Object>("background",
                                                                                                                   16,
                                                                                                                   *this,
                                                                                                                   pos_t({0,0}));
            this->addObject(transparentBackground);
            transparentBackground->getComponent<engine::MovementComponent>()->setPosition(0, 0);
            for (auto &e : _buttons) {
                this->addObject(e);
                e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
            }
            std::shared_ptr<engine::Input> input = std::make_shared<engine::Input>("inputBox", 19, nullptr, nullptr, nullptr, *this, pos_t({1600/2-150, 900/2-40}));
            input->getComponent<engine::MovementComponent>()->setPosition(1600/2-150, 900/2-40);
            this->addObject(input);

            std::shared_ptr<rtype::engine::Text> title = std::make_shared<rtype::engine::Text>(
                    "title",
                    "Enter a room Name",
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-300,0}));
            //center text
            sf::FloatRect textRect = title->getSfmlText()->getLocalBounds();
            title->getSfmlText()->setOrigin(textRect.left + textRect.width/2.0f,
                                            textRect.top  + textRect.height/2.0f);
            title->getSfmlText()->setPosition(sf::Vector2f(1600/2.0f,80));
            _texts.push_back(title);
            for (auto &e : _texts) {
                this->addObject(e);
            }
        }
    }
}