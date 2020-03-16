//
// Created by simon on 27/11/19.
//

#include "settings.hpp"
#include "Menu.hpp"


namespace rtype {
    namespace client {

        Settings::Settings(const std::string &name, rtype::engine::ISceneManager &sceneManager) : Scene(name, sceneManager)
        {
            std::shared_ptr<rtype::engine::Button> exitButton = std::make_shared<rtype::engine::Button>(
                    "exit",
                    9,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
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
            std::shared_ptr<rtype::engine::Button> back = std::make_shared<rtype::engine::Button>(
                    "Back",
                    11,
                    [](engine::Button &button) {
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        if (button.getScene().getSceneManager().sceneExist("menu"))
                            button.getScene().getSceneManager().getScene("menu")->setIsHidden(false);
                        else {
                            Menu menu("menu", button.getScene().getSceneManager());
                            button.getScene().getSceneManager().addScene(std::make_shared<rtype::engine::Scene>(menu));
                        }
                        button.getScene().getSceneManager().getScene("settings")->setIsHidden(true);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(12);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(11);
                    },
                    *this,
                    pos_t({100, 100})
            );

            std::shared_ptr<rtype::engine::Button> minusFrameRate = std::make_shared<rtype::engine::Button>(
                    "minus",
                    55,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        int actual = std::stoi(std::static_pointer_cast<engine::Text>(button.getScene().getObject("frameRateCounter"))->getText());
                        actual = actual - 1;
                        std::static_pointer_cast<engine::Text>(button.getScene().getObject("frameRateCounter"))->setText(std::to_string(actual));
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(56);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(55);
                    },
                    *this,
                    pos_t({(1600/2)-450, 400})
            );

            std::shared_ptr<rtype::engine::Button> plusFrameRate = std::make_shared<rtype::engine::Button>(
                    "plus",
                    57,
                    [](engine::Button &button){
                        button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                        int actual = std::stoi(std::static_pointer_cast<engine::Text>(button.getScene().getObject("frameRateCounter"))->getText());
                        actual = actual + 1;
                        std::static_pointer_cast<engine::Text>(button.getScene().getObject("frameRateCounter"))->setText(std::to_string(actual));
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(56);
                    },
                    [](engine::Button &button){
                        button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(55);
                    },
                    *this,
                    pos_t({(1600/2.0)+150, 400})
            );

            _buttons.push_back(exitButton);
            _buttons.push_back(back);
            _buttons.push_back(minusFrameRate);
            _buttons.push_back(plusFrameRate);
            for (auto &e : _buttons) {
                e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
                this->addObject(e);
            }

            std::shared_ptr<rtype::engine::Text> title = std::make_shared<engine::Text>(
                    "title",
                    "SETTINGS",
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-200,50})
            );
            std::shared_ptr<rtype::engine::Text> frameRate = std::make_shared<engine::Text>(
                    "frameRateCounter",
                    "60",
                    100,
                    sf::Color(sf::Color::Red),
                    *this,
                    pos_t({1600/2-50,380})
            );
            std::shared_ptr<rtype::engine::Text> frameRateTitle = std::make_shared<engine::Text>(
                    "frameRateTitle",
                    "Frame Rate",
                    70,
                    sf::Color(sf::Color::White),
                    *this,
                    pos_t({1600/2-200,280})
            );
            _texts.push_back(title);
            _texts.push_back(frameRate);
            _texts.push_back(frameRateTitle);
            for (auto &e : _texts) {
                this->addObject(e);
            }
        }

        void Settings::display(sf::RenderWindow &window)
        {
            static int oldFrameRate = 60;
            int actual = std::stoi(std::static_pointer_cast<engine::Text>(this->getObject("frameRateCounter"))->getText());

            if (oldFrameRate != actual) {
                window.setFramerateLimit(actual);
            }
            for (auto &e : _buttons) {
                e->display(window);
            }
            for (auto &e : _texts) {
                e->display(window);
            }
        }
    }
}
