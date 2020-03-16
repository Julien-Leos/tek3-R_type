/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** LuaApi
*/

#include "LuaApi.hpp"

namespace rtype {

namespace game {


lua_State *LuaApi::newState()
{
    lua_State *L;

    L = luaL_newstate();
    luaL_openlibs(L);
    return (L);
}

void LuaApi::pushFunction(lua_State *luaState, int (*ptr)(lua_State *L), const std::string &name)
{
    lua_register(luaState, name.c_str(), ptr);
}

float LuaApi::computeDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0); 
}

int LuaApi::getAIPosition(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    const pos_t pos = ai->getComponent<engine::MovementComponent>()->getPosition();

    lua_newtable(luaState);
    lua_pushstring(luaState, "x");
    lua_pushinteger(luaState, pos.x);
    lua_settable(luaState, -3);
    lua_pushstring(luaState, "y");
    lua_pushinteger(luaState, pos.y);
    lua_settable(luaState, -3);
    return 1;
}

int LuaApi::getAISize(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    const std::pair<float, float> pos = ai->getComponent<engine::AnimationComponent>()->getSize();

    lua_newtable(luaState);
    lua_pushstring(luaState, "x");
    lua_pushinteger(luaState, pos.first);
    lua_settable(luaState, -3);
    lua_pushstring(luaState, "y");
    lua_pushinteger(luaState, pos.second);
    lua_settable(luaState, -3);
    return 1;
}

int LuaApi::getPlayerPosition(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::vector<std::shared_ptr<engine::IObject>> objects = ai->getScene().getObjects();
    pos_t pos = {-1, -1};
    float mostShortDistance = -1;
    pos_t tmp = {0, 0};

    for (auto &i: objects) {
        if (i->getName() == "player") {
            tmp = i->getComponent<engine::MovementComponent>()->getPosition();
            if (mostShortDistance == -1
            || computeDistance(pos.x, pos.y, tmp.x, tmp.y) < mostShortDistance) {
                pos = tmp;
                mostShortDistance = computeDistance(pos.x, pos.y, tmp.x, tmp.y);
            }
        }
    }
    lua_newtable(luaState);
    lua_pushstring(luaState, "x");
    lua_pushinteger(luaState, pos.x);
    lua_settable(luaState, -3);
    lua_pushstring(luaState, "y");
    lua_pushinteger(luaState, pos.y);
    lua_settable(luaState, -3);
    return 1;
}

int LuaApi::getElapsedTimeSinceFire(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    float elapsedTime = ai->getLastFire();

    lua_pushnumber(luaState, elapsedTime);
    return 1;
}

int LuaApi::getElapsedTimeSinceDirection(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    float elapsedTime = ai->getLastDirection();

    lua_pushnumber(luaState, elapsedTime);
    return 1;
}

int LuaApi::setDirection(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    float x = lua_tonumber(luaState, 2);
    float y = lua_tonumber(luaState, 3);
    network::ServerNetwork * network = dynamic_cast<network::ServerNetwork *>(ai->getScene().getSceneManager().getNetwork());
    protocol_t protocol;
    EMPTY_PROTOCOL(protocol);

    ai->setLastDirection(0);
    protocol.opcode = 102;
    protocol.data = ai->getId();
    protocol.object.velocity = {x, y};
    network->sendUDPPacket(protocol, network->getUdpConnection());
    ai->getComponent<engine::MovementComponent>()->setSpeed(x, y);
    return 0;
}

int LuaApi::fire(lua_State *luaState)
{
    AI *ai = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::string type = lua_tostring(luaState, 2);
    float x = lua_tonumber(luaState, 3);
    float y = lua_tonumber(luaState, 4);

    ai->setLastFire(0);
    if (type == "bullet") {
        ai->getComponent<LauncherComponent>()->fireBullet({x, y});
    } else if (type == "rocket") {
        ai->getComponent<LauncherComponent>()->fireRocket({x, y});
    }
    return 0;
}

int LuaApi::createMob(lua_State *luaState)
{
    Map *map = static_cast<Map *>(lua_touserdata(luaState, 1));
    std::string type = lua_tostring(luaState, 2);
    float x = lua_tonumber(luaState, 3);
    float y = lua_tonumber(luaState, 4);

    map->createMob(type, pos_t({x, y}));
    return 0;
}

int LuaApi::getStartTime(lua_State *luaState)
{
    Map *map = static_cast<Map *>(lua_touserdata(luaState, 1));
    float lastCreation = map->getStartTime();

    lua_pushnumber(luaState, lastCreation);
    return 1;
}

int LuaApi::getMobsCreated(lua_State *luaState)
{
    Map *map = static_cast<Map *>(lua_touserdata(luaState, 1));
    unsigned mobsCreated = map->getMobsCreated();

    lua_pushinteger(luaState, mobsCreated);
    return 1;
}

int LuaApi::getMobsKilled(lua_State *luaState)
{
    Map *map = static_cast<Map *>(lua_touserdata(luaState, 1));
    unsigned mobsKilled = map->getMobsKilled();

    lua_pushinteger(luaState, mobsKilled);
    return 1;
}

int LuaApi::loadNextLevel(lua_State *luaState)
{
    Map *map = static_cast<Map *>(lua_touserdata(luaState, 1));

    map->loadNextLevel();
    return 0;
}

}

}
