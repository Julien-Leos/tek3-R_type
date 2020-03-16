/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AI
*/

#include "AI.hpp"

namespace rtype {
namespace game {

AI::AI(const std::string &name, const unsigned &spriteId, engine::IScene &scene, const std::string &fileName, const pos_t &position)
: Object("ai_" + name, spriteId, scene, position), _fileName(AI_PATH + fileName)
{
    addComponent<LauncherComponent>(std::make_shared<LauncherComponent>(*this));
    getComponent<engine::MovementComponent>()->setFreeMoving(true);
    _luaState = LuaApi::newState();
    LuaApi::pushFunction(_luaState, &LuaApi::getAIPosition, "getAIPosition");
    LuaApi::pushFunction(_luaState, &LuaApi::getElapsedTimeSinceFire, "getElapsedTimeSinceFire");
    LuaApi::pushFunction(_luaState, &LuaApi::getElapsedTimeSinceDirection, "getElapsedTimeSinceDirection");
    LuaApi::pushFunction(_luaState, &LuaApi::getPlayerPosition, "getPlayerPosition");
    LuaApi::pushFunction(_luaState, &LuaApi::setDirection, "setDirection");
    LuaApi::pushFunction(_luaState, &LuaApi::fire, "fire");
    lua_pushlightuserdata(_luaState, this);
    lua_setglobal(_luaState, "AI");
}

AI::~AI()
{
    lua_gc(_luaState , LUA_GCCOLLECT, 0);
    lua_close(_luaState);
}

float AI::update(const float &actualTime)
{
    float delta = Object::update(actualTime);

    if (getComponent<engine::MovementComponent>()->getPosition().x < -100
    || getComponent<engine::MovementComponent>()->getPosition().x > WINDOW_WIDTH + 50) {
        _scene.removeObject(getId());
        std::static_pointer_cast<Map>(_scene.getObject("map"))->addAMobKilled();
        return delta;
    }
    _lastAction += delta;
    _lastFire += delta;
    _lastDirection += delta;
    if (_lastAction > 0.1) {
        makeDecision();
        _lastAction = 0;
    }
    return delta;
}

void AI::makeDecision()
{
    if (_luaState)
        luaL_dofile(_luaState, _fileName.c_str());
}

void AI::setLastFire(const float &lastFire)
{
    _lastFire = lastFire;
}

const float &AI::getLastFire() const
{
    return _lastFire;
}

void AI::setLastDirection(const float &lastDirection)
{
    _lastDirection = lastDirection;
}

const float &AI::getLastDirection() const
{
    return _lastDirection;
}

}
}
