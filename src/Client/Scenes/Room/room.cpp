//
// Created by simon on 30/11/19.
//

#include "listMatch.hpp"
#include "lobby.hpp"
#include "Menu.hpp"
#include "room.hpp"

rtype::client::RoomScene::RoomScene(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::string &username, std::string &roomName, const int & roomId) : Scene(name, sceneManager), _username(username), _roomName(roomName), _roomId(roomId)
{
    std::shared_ptr<rtype::engine::Button> leave = std::make_shared<rtype::engine::Button>(
            "leave",
            31,
            [this](engine::Button &button) {
                button.getScene().getSceneManager().getSoundManager()->playSong("buttonClicked");
                protocol_t data;
                EMPTY_PROTOCOL(data);
                data.opcode = 23;
                data.data = _roomId;
                data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection);
            },
            [](engine::Button &button) {
                button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(32);
            },
            [](engine::Button &button){
                button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(31);
            },
            *this,
            pos_t({100, 150}));

    std::shared_ptr<rtype::engine::Button> ready = std::make_shared<rtype::engine::Button>(
            "ready",
            27,
            [this](engine::Button &button){
                button.getScene().getSceneManager().getSoundManager()->playSong("ready");
                protocol_t data;
                EMPTY_PROTOCOL(data);
                data.opcode = 26;
                data.data = _roomId;
                data.clientId = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getClientId();
                const network::TcpConnection::pointer connection = dynamic_cast<network::ClientNetwork *>(button.getScene().getSceneManager().getNetwork())->getTcpConnection();
                button.getScene().getSceneManager().getNetwork()->sendTCPPacket(data, connection);
            },
            [](engine::Button &button) {
                button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(28);
            },
            [](engine::Button &button){
                button.getComponent<rtype::engine::AnimationComponent>()->changeSprite(27);
            },
            *this,
            pos_t({1600-400, 900 - 100}));

    _buttons.push_back(leave);
    _buttons.push_back(ready);
    for (auto &e : _buttons) {
        this->addObject(e);
        e->getComponent<engine::MovementComponent>()->setPosition(e->getButtonPos().x, e->getButtonPos().y);
    }

    std::shared_ptr<rtype::engine::Text> title = std::make_shared<rtype::engine::Text>(
            "title",
            roomName,
            100,
            sf::Color(sf::Color::Red),
            *this,
            pos_t({1600/2-300,0}));
    _texts.push_back(title);
    for (auto &e : _texts) {
        this->addObject(e);
    }

    std::shared_ptr<rtype::engine::Object> panel = std::make_shared<rtype::engine::Object>("panel",
                                                                                           13,
                                                                                           *this,
                                                                                           pos_t({1600/2-300, 900-400}));

    this->addObject(panel);
    panel->getComponent<engine::MovementComponent>()->setPosition(1600/2-300, 900-750);

}

const std::string &rtype::client::RoomScene::getUsername() const
{
    return _username;
}