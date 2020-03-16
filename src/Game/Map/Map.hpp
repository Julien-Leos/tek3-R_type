/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Object.hpp"
#include "LuaApi.hpp"
#include "ServerNetwork.hpp"

#ifdef __APPLE__
    #define MAP_PATH "CPP_rtype_2019/assets/maps/"
#elif __linux__
    #define MAP_PATH "assets/maps/"
#elif _WIN32
    #define MAP_PATH "assets/maps/"
#endif /* __APPLE__ */

namespace rtype {
    namespace game {
        class AI;
        class Map : public engine::Object {
            public:
                Map(engine::IScene &scene);
                ~Map() = default;

                float update(const float &actualTime) override;
                int loadNextLevel();
                void createMob(const std::string &type, const pos_t &pos);
                const unsigned &getMobsCreated() const;
                const unsigned &getMobsKilled() const;
                void addAMobKilled();
                const float &getStartTime() const;
                lua_State *getState() const;

            private:
                float       _lastAction = 0;
                lua_State * _luaState = nullptr;
                unsigned    _level = 1;
                std::string _fileName = "";
                float       _start = 0;
                unsigned    _mobsCreated = 0;
                unsigned    _mobsKilled = 0;
                std::vector<std::shared_ptr<AI>> _objs;
        };
    }
}

#endif /* !MAP_HPP_ */
