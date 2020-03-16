//
// Created by simon on 27/11/19.
//

#ifndef RTYPE_SETTINGS_HPP
#define RTYPE_SETTINGS_HPP

#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "Button.hpp"

namespace rtype {
    namespace client {
        class Settings : public rtype::engine::Scene
        {
        public:
            Settings(const std::string &name, rtype::engine::ISceneManager &sceneManager);
            void display(sf::RenderWindow &window) override;


        protected:

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;

        };
    }
}


#endif //RTYPE_SETTINGS_HPP
