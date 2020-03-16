//
// Created by simon on 25/11/19.
//

#ifndef RTYPE_MENU_HPP
#define RTYPE_MENU_HPP

#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "Button.hpp"
#include "Input.hpp"

namespace rtype {
    namespace client {
        class Button;

        class Menu : public rtype::engine::Scene {
        public:
            Menu(const std::string &name, rtype::engine::ISceneManager &sceneManager);
            void update(const float &actualTime) override;

            virtual ~Menu();

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;

        };
    }
}

#endif //RTYPE_MENU_HPP
