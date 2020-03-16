/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Protocol
*/

#include "Protocol.hpp"
#include "Client.hpp"

namespace rtype {
namespace client {
    Protocol::Protocol(const Client & client) : _client(client)
    {
        _opFuncList.insert(std::make_pair(1, &Protocol::opInit));
        _opFuncList.insert(std::make_pair(11, &Protocol::opConnect));
        _opFuncList.insert(std::make_pair(13, &Protocol::opDisconnect));
        _opFuncList.insert(std::make_pair(21, &Protocol::opCreateRoom));
        _opFuncList.insert(std::make_pair(22, &Protocol::opJoinRoom));
        _opFuncList.insert(std::make_pair(23, &Protocol::opLeaveRoom));
        _opFuncList.insert(std::make_pair(24, &Protocol::opDeleteRoom));
        _opFuncList.insert(std::make_pair(25, &Protocol::opGetRoom));
        _opFuncList.insert(std::make_pair(26, &Protocol::opPlayerReady));
        _opFuncList.insert(std::make_pair(27, &Protocol::opGetPlayer));
        _opFuncList.insert(std::make_pair(31, &Protocol::opStartGame));
        _opFuncList.insert(std::make_pair(32, &Protocol::opEndGame));
        _opFuncList.insert(std::make_pair(101, &Protocol::opCreateObject));
        _opFuncList.insert(std::make_pair(102, &Protocol::opUpdateObject));
        _opFuncList.insert(std::make_pair(103, &Protocol::opDeleteObject));
        _opFuncList.insert(std::make_pair(111, &Protocol::opUpdateScore));
        _opFuncList.insert(std::make_pair(121, &Protocol::opUpdateHealth));
    }

    void Protocol::browseProtocols(const protocol_t &data, const std::string &string)
    {
        auto opFunc = _opFuncList[data.opcode];

        if (!opFunc)
            return;
        (this->*opFunc)(data, string);
    }

    void Protocol::opInit(const protocol_t & data, const std::string &text)
    {
        protocol_t packet;
        EMPTY_PROTOCOL(packet);

        _client._network->setClientId(data.clientId);
        packet.clientId = data.clientId;

        _client._network->sendUDPPacket(packet, _client._network->getUdpConnection());
        static_cast<void>(text);
    }

    void Protocol::opConnect(const protocol_t & data, const std::string &text)
    {
        std::string name(text);
        if (_client._display->getSceneManager()->sceneExist("lobby")) {
            std::static_pointer_cast<client::Lobby>(_client._display->getSceneManager()->getScene("lobby"))->setUsername(name);
            _client._display->getSceneManager()->getScene("lobby")->setIsHidden(false);
        } else {
            _client._display->getSceneManager()->addScene(std::make_shared<Lobby>("lobby", *_client._display->getSceneManager(), name));
        }
        if (_client._display->getSceneManager()->sceneExist("listRoom")) {
                _client._display->getSceneManager()->getScene("listRoom")->setIsHidden(false);
        } else {
            std::vector<std::string> vectListRooms = {};
            _client._display->getSceneManager()->addScene(std::make_shared<ListRoom>("listRoom", *_client._display->getSceneManager(), vectListRooms, std::pair<int,int>(0,6)));
        }
        _client._display->getSceneManager()->getScene("menu")->setIsHidden(true);
        _client._display->getSceneManager()->getScene("usernameField")->setIsHidden(true);
        static_cast<void>(data);
    }

    void Protocol::opDisconnect(const protocol_t & data, const std::string &text)
    {
        static_cast<void>(data);
        static_cast<void>(text);
    }

    void Protocol::opCreateRoom(const protocol_t & data, const std::string &text)
    {
        std::string roomName(text);

        std::static_pointer_cast<ListRoom>(_client._display->getSceneManager()->getScene("listRoom"))->addRoom(roomName, data.data);
    }

    void Protocol::opJoinRoom(const protocol_t & data, const std::string &text)
    {
        if (_client._display->getSceneManager()->sceneExist("roomGame")) {
            _client._display->getSceneManager()->getScene("roomGame")->setIsHidden(false);
        } else {
            std::string username = std::static_pointer_cast<client::Lobby>(_client._display->getSceneManager()->getScene("lobby"))->getUsername();
            std::string roomName = "Waiting for players ...";
            _client._display->getSceneManager()->addScene(std::make_shared<RoomScene>("roomGame", *_client._display->getSceneManager(), username, roomName, data.data));
        }
        if (_client._display->getSceneManager()->sceneExist("listPlayer")) {
            _client._display->getSceneManager()->getScene("listPlayer")->setIsHidden(false);
        } else {
            std::vector<std::string> vectPlayers = {};
            _client._display->getSceneManager()->addScene(std::make_shared<ListPlayers>("listPlayer", *_client._display->getSceneManager(), vectPlayers, std::pair<int,int>(0,4)));
        }
        _client._display->getSceneManager()->getScene("lobby")->setIsHidden(true);
        _client._display->getSceneManager()->getScene("listRoom")->setIsHidden(true);
        static_cast<void>(text);
    }

    void Protocol::opLeaveRoom(const protocol_t & data, const std::string &text)
    {
        std::static_pointer_cast<ListPlayers>(_client._display->getSceneManager()->getScene("listPlayer"))->removePlayer(data.data);
        if (_client._network->getClientId() == data.data) {
            std::static_pointer_cast<ListRoom>(_client._display->getSceneManager()->getScene("listRoom"))->getElements().clear();
            if (_client._display->getSceneManager()->sceneExist("lobby")) {
                _client._display->getSceneManager()->getScene("lobby")->setIsHidden(false);
            } else {
                std::string username(text);
                _client._display->getSceneManager()->addScene(std::make_shared<Lobby>("lobby", *_client._display->getSceneManager(), username));
            }
            if (_client._display->getSceneManager()->sceneExist("listRoom")) {
                _client._display->getSceneManager()->getScene("listRoom")->setIsHidden(false);
            }
            _client._display->getSceneManager()->getScene("listPlayer")->setIsHidden(true);
            _client._display->getSceneManager()->getScene("roomGame")->setIsHidden(true);
        }
    }

    void Protocol::opDeleteRoom(const protocol_t & data, const std::string &text)
    {
        std::static_pointer_cast<ListPlayers>(_client._display->getSceneManager()->getScene("listPlayer"))->getElements().clear();
        static_cast<void>(text);
        static_cast<void>(data);
    }

    void Protocol::opGetRoom(const protocol_t & data, const std::string &text)
    {
        std::string roomName(text);
        std::static_pointer_cast<ListRoom>(_client._display->getSceneManager()->getScene("listRoom"))->addRoom(roomName, data.data);
    }

    void Protocol::opPlayerReady(const protocol_t & data, const std::string &text)
    {
        std::static_pointer_cast<ListPlayers>(_client._display->getSceneManager()->getScene("listPlayer"))->addPlayerReady(data.data);
        static_cast<void>(text);
    }

    void Protocol::opGetPlayer(const protocol_t & data, const std::string &text)
    {
        std::string playerName(text);
        std::static_pointer_cast<ListPlayers>(_client._display->getSceneManager()->getScene("listPlayer"))->addPlayer(playerName, data.data);
    }

    void Protocol::opCreateObject(const protocol_t & data, const std::string &text)
    {
        auto gameScene = _client._display->getSceneManager()->getScene("game");
        std::shared_ptr<rtype::engine::IObject> obj;

        if (data.clientId == _client._network->getClientId()) {
            obj = gameScene->addObject("ownSpaceship", data.object.type, data.data, *gameScene, data.object.pos);
            obj->getComponent<engine::MovementComponent>()->setFreeMoving(true);
        } else {
            obj = gameScene->addObject("object", data.object.type, data.data, *gameScene, data.object.pos);
            if (data.object.velocity.x != -1 && data.object.velocity.y != -1)
                obj->getComponent<engine::MovementComponent>()->setSpeed(data.object.velocity.x, data.object.velocity.y);
            if (data.object.type == 24)
                _client._display->getSceneManager()->getSoundManager()->playSong("bullet");
            else if (data.object.type == 54)
                _client._display->getSceneManager()->getSoundManager()->playSong("rocket");
            obj->getComponent<engine::MovementComponent>()->setFreeMoving(true);
        }
        if (data.object.isCollide == 1)
            obj->getComponent<engine::MovementComponent>()->setBlocking(true);
        static_cast<void>(text);
    }

    void Protocol::opUpdateObject(const protocol_t & data, const std::string &text)
    {
        auto object = _client._display->getSceneManager()->getScene("game")->getObject(data.data);

        if (data.object.pos.x != -1 && data.object.pos.y != -1)
            object->getComponent<engine::MovementComponent>()->setPosition(data.object.pos.x, data.object.pos.y);
        if (data.object.velocity.x != -1 && data.object.velocity.y != -1)
            object->getComponent<engine::MovementComponent>()->setSpeed(data.object.velocity.x, data.object.velocity.y);
        if (data.object.type != 0)
            object->getComponent<engine::AnimationComponent>()->changeSprite(data.object.type);
        static_cast<void>(text);
    }

    void Protocol::opDeleteObject(const protocol_t & data, const std::string &text)
    {
        static_cast<void>(text);
        _client._display->getSceneManager()->getScene("game")->removeObject(data.data);
    }

    void Protocol::opStartGame(const protocol_t & data, const std::string &text)
    {
        const std::string username =  std::static_pointer_cast<RoomScene>(_client._display->getSceneManager()->getScene("roomGame"))->getUsername();
        _client._network->initNetworkEndpoint(data.data);
        _client._network->start();

        std::shared_ptr<engine::Scene> game = std::make_shared<engine::Scene>("game", *(_client._display->getSceneManager()));
        std::shared_ptr<GuiGame> gui = std::make_shared<GuiGame>("gui", *(_client._display->getSceneManager()), username);
        _client._display->getSceneManager()->addScene(game);
        _client._display->getSceneManager()->addScene(gui);

        _client._display->getSceneManager()->getScene("roomGame")->setIsHidden(true);
        _client._display->getSceneManager()->getScene("listPlayer")->setIsHidden(true);
        static_cast<void>(text);
    }

    void Protocol::opUpdateScore(const protocol_t & data, const std::string &text)
    {
        static_cast<void>(text);
        std::static_pointer_cast<client::GuiGame>(_client._display->getSceneManager()->getScene("gui"))->setScore(data.data);
    }

    void Protocol::opEndGame(const protocol_t & data, const std::string &text)
    {
        _client._display->getSceneManager()->removeScene("game");
        _client._display->getSceneManager()->removeScene("gui");
        _client._display->getSceneManager()->getScene("menu")->setIsHidden(false);
        static_cast<void>(text);
        static_cast<void>(data);
    }

    void Protocol::opUpdateHealth(const protocol_t & data, const std::string &text)
    {
        static_cast<void>(text);
        std::static_pointer_cast<client::GuiGame>(_client._display->getSceneManager()->getScene("gui"))->setLife(data.data);
    }
}
}