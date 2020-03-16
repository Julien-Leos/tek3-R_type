//
// Created by simon on 30/11/19.
//

#ifndef RTYPE_ROOM_HPP
#define RTYPE_ROOM_HPP

#include "Button.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"

namespace rtype {
    namespace client {
        class RoomScene : public rtype::engine::Scene
        {
        public:
            RoomScene(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::string &username, std::string &roomName, const int & roomId);

            int getRoomId(void) const { return _roomId; };
            const std::string &getUsername(void) const;
        protected:

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;
            std::vector<std::string> _players;
            std::string _username;
            std::string _roomName;
            int         _roomId;

        };
    }
}


#endif //RTYPE_ROOM_HPP
