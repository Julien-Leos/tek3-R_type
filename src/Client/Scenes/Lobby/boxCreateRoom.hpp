//
// Created by simon on 27/11/19.
//

#ifndef RTYPE_BOXCREATEROOM_HPP
#define RTYPE_BOXCREATEROOM_HPP

#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "Button.hpp"

namespace rtype {
    namespace client {
        class BoxCreateRoom : public rtype::engine::Scene
        {
        public:
            BoxCreateRoom(const std::string &name, rtype::engine::ISceneManager &sceneManager);

        protected:

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;

        };
    }
}


#endif //RTYPE_BOXCREATEROOM_HPP
