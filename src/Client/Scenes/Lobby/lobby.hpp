//
// Created by simon on 27/11/19.
//

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include "Button.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"

namespace rtype {
    namespace client {
        class Lobby : public rtype::engine::Scene
        {
        public:
            Lobby(const std::string &name, rtype::engine::ISceneManager &sceneManager, std::string &username);
            const std::string &getUsername() const;
            bool isAlreadyLogged();
            void setUsername(const std::string &username);
            void update(const float &actualTime) override;
            virtual ~Lobby();

        protected:

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;
            std::string _username;

        };
    }
}




#endif //RTYPE_LOBBY_HPP
