/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Map
*/

#include "Map.hpp"

namespace rtype {

namespace game {

Map::Map(engine::IScene &scene)
: Object("map", 0, scene)
{
    _fileName = MAP_PATH + std::string("level-1.lua");
    getComponent<engine::AnimationComponent>()->disable();
    getComponent<engine::MovementComponent>()->disable();
    _luaState = LuaApi::newState();
    LuaApi::pushFunction(_luaState, LuaApi::createMob, "createMob");
    LuaApi::pushFunction(_luaState, LuaApi::loadNextLevel, "loadNextLevel");
    LuaApi::pushFunction(_luaState, LuaApi::getStartTime, "getStartTime");
    LuaApi::pushFunction(_luaState, LuaApi::getMobsCreated, "getMobsCreated");
    LuaApi::pushFunction(_luaState, LuaApi::getMobsKilled, "getMobsKilled");
}

float Map::update(const float &actualTime)
{
    float delta = Object::update(actualTime);
    std::vector<std::string> tab;

    _lastAction += delta;
    _start += delta;
    if (_lastAction >= 0.5 && _luaState) {
        luaL_dofile(_luaState, _fileName.c_str());
        // protocol_t protocol;
        // EMPTY_PROTOCOL(protocol);
        // network::ServerNetwork * network = dynamic_cast<network::ServerNetwork *>(_scene.getSceneManager().getNetwork());
        // std::shared_ptr<AI> object = std::make_shared<AI>("dumb", 35, _scene, "dumb" + std::string(".lua"), pos_t({1600, 450}));


        // _scene.addObject(object);
        // protocol.data = object->getId();
        // protocol.opcode = 101;
        // protocol.object.pos = pos_t({1600, 450});
        // protocol.object.type = 35;
        // network->sendUDPPacket(protocol, network->getUdpConnection());
        _lastAction = 0;
    }
    return delta;
}

int Map::loadNextLevel()
{
    std::fstream fs;
    
    _level++;
    _mobsKilled = 0;
    _mobsCreated = 0;
    _start = 0;
    fs.open(MAP_PATH + std::string("level-") + std::to_string(_level) + std::string(".lua"));
    if (!fs.is_open())
        return 1;
    _fileName = MAP_PATH + std::string("level-") + std::to_string(_level) + std::string(".lua");
    return 0;
}

void Map::createMob(const std::string &type, const pos_t &pos)
{
    protocol_t protocol;
    EMPTY_PROTOCOL(protocol);
    unsigned spriteId = 35;
    network::ServerNetwork * network = dynamic_cast<network::ServerNetwork *>(_scene.getSceneManager().getNetwork());

    if (type == "dumb") {
        spriteId = 35;
    } else if (type == "random") {
        spriteId = 34;
    } else if (type == "shooter") {
        spriteId = 36;
    } else if (type == "chaser") {
        spriteId = 37;
    } else if (type == "boss") {
        spriteId = 38;
    }

    std::shared_ptr<AI> object = std::make_shared<AI>(type, spriteId, _scene, type + std::string(".lua"), pos);

    _scene.addObject(object);
    protocol.data = object->getId();
    protocol.opcode = 101;
    protocol.object.pos = pos;
    protocol.object.type = spriteId;
    network->sendUDPPacket(protocol, network->getUdpConnection());
    _mobsCreated++;
}

const unsigned &Map::getMobsCreated() const
{
    return _mobsCreated;
}

const unsigned &Map::getMobsKilled() const
{
    return _mobsKilled;
}

void Map::addAMobKilled()
{
    _mobsKilled++;
}

const float &Map::getStartTime() const
{
    return _start;
}

lua_State *Map::getState() const
{
    return _luaState;
}

}

}
