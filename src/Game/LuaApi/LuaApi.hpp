/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** LuaApi
*/

#ifndef LUAAPI_HPP_
#define LUAAPI_HPP_

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <iostream>
#include "Map.hpp"
#include "AI.hpp"
#include "LauncherComponent.hpp"

namespace rtype {
namespace game {

/**
 * @brief LuaApi is the api to do the link between LUA and C++.
 * It communicates thanks to the stack by pushing C++ variables into it.
 * Lua gets it and uses it to compute the ai movements.
 *
 */
class LuaApi {
    public:
        LuaApi() = default;
        ~LuaApi() = default;

        /**
         * @brief Get the Player Position object
         *
         * @param L
         * @return int
         */
        static int getPlayerPosition(lua_State *L);

        /**
         * @brief Get the AI Position
         *
         * @param L
         * @return int
         */
        static int getAIPosition(lua_State *L);

        /**
         * @brief Get the AI Size
         *
         * @param L
         * @return int
         */
        static int getAISize(lua_State *L);

        /**
         * @brief Get the number of seconds elapsed since last action
         *
         * @param L
         * @return int
         */
        static int getElapsedTimeSinceFire(lua_State *L);

        /**
         * @brief Get the number of seconds elapsed since last direction
         * 
         * @param L 
         * @return int 
         */
        static int getElapsedTimeSinceDirection(lua_State *L);

        /**
         * @brief Push a C++ function to the stack
         *
         * @param luaState
         * @param ptr function pointer
         * @param name name of the function (for Lua)
         */
        static void pushFunction(lua_State *L, int (*ptr)(lua_State *L), const std::string &name);

        /**
         * @brief Create a new luaState to communicate between C++ and Lua with the stack
         *
         * @return lua_State* new state
         */
        static lua_State *newState();

        /**
         * @brief Set the Direction object
         *
         * @param L
         * @return int
         */
        static int setDirection(lua_State *L);

        /**
         * @brief Fire a bullet or a rocket at a given direction
         * 
         * @param L 
         * @return int 
         */
        static int fire(lua_State *L);

        /**
         * @brief Create a mob object
         * 
         * @param L 
         * @return int 
         */
        static int createMob(lua_State *L);

        /**
         * @brief Get time elapsed since last mob creation
         * 
         * @param L 
         * @return int 
         */
        static int getStartTime(lua_State *L);

        /**
         * @brief Get the number of mobs created
         * 
         * @param L 
         * @return int 
         */
        static int getMobsCreated(lua_State *L);

        /**
         * @brief Get the number of mobs created
         * 
         * @param L 
         * @return int 
         */
        static int getMobsKilled(lua_State *L);

        /**
         * @brief Load the next level
         * 
         * @param L 
         * @return int 
         */
        static int loadNextLevel(lua_State *L);
    
    private:
        static float computeDistance(float x1, float y1, float x2, float y2);
};

}
}

#endif /* !LUAAPI_HPP_ */
