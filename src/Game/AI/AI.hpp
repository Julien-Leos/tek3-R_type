/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <iostream>
#include "LuaApi.hpp"
#include "Object.hpp"
#include "LauncherComponent.hpp"

#ifdef __APPLE__
    #define AI_PATH "CPP_rtype_2019/artificialIntelligences/"
#elif __linux__
    #define AI_PATH "assets/artificialIntelligences/"
#elif _WIN32
    #define AI_PATH "assets/artificialIntelligences/"
#endif /* __APPLE__ */

namespace rtype {
namespace game {

class AI : public engine::Object {
	public:
		AI(const std::string &name, const unsigned &spriteId, engine::IScene &scene, const std::string &fileName, const pos_t &position = {0, 0});
		virtual ~AI();

        float update(const float &actualTime) override;

        void makeDecision();

        void setLastFire(const float &lastFire);
        const float &getLastFire() const;

        void setLastDirection(const float &lastDirection);
        const float &getLastDirection() const;

    private:
        float _lastAction = 0;
        std::string _fileName = "";
        lua_State * _luaState = nullptr;
        float _lastFire = 0;
        float _lastDirection = 0;
};

}
}

#endif /* !AI_HPP_ */
