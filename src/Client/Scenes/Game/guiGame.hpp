//
// Created by simon on 01/12/19.
//

#ifndef RTYPE_GUIGAME_HPP
#define RTYPE_GUIGAME_HPP

#include "Button.hpp"
#include "Text.hpp"
#include "Scene.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"

namespace rtype {
    namespace client {
        class GuiGame : public rtype::engine::Scene
        {
        public:
            GuiGame(const std::string &name, rtype::engine::ISceneManager &sceneManager, const std::string &username);

            std::vector<std::shared_ptr<engine::Button>> getButtons() const;
            void setButtons(const std::vector<std::shared_ptr<engine::Button>> &buttons);
            std::vector<std::shared_ptr<engine::Text>> getTexts() const;
            void setTexts(const std::vector<std::shared_ptr<engine::Text>> &texts);
            unsigned int getLife() const;
            void setLife(unsigned int life);
            unsigned int getScore() const;
            void setScore(unsigned int score);
            const std::string &getUsername() const;
            void setUsername(const std::string &username);

            void update(const float &actualTime) override;

        protected:

        private:
            std::vector<std::shared_ptr<rtype::engine::Button>> _buttons;
            std::vector<std::shared_ptr<rtype::engine::Text>> _texts;
            std::string _username;
            unsigned int _life;
            unsigned int _score;
        };
    }
}



#endif //RTYPE_GUIGAME_HPP
