//
// Created by simon on 29/11/19.
//

#ifndef RTYPE_USERNAMEFIELD_HPP
#define RTYPE_USERNAMEFIELD_HPP

#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "Button.hpp"
#include "Input.hpp"

namespace rtype {
    namespace client {

        class userNameFIeld : public rtype::engine::Scene {
            public:
                userNameFIeld(const std::string &name, rtype::engine::ISceneManager &sceneManager);

            private:
                std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
                std::vector<std::shared_ptr<rtype::engine::Text>> _texts;

        };
    }
}


#endif //RTYPE_USERNAMEFIELD_HPP
