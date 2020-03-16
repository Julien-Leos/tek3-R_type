/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "Button.hpp"
#include "IScene.hpp"
#include "Text.hpp"

namespace rtype {
    namespace engine {
        class Input : public Button {
            public:
                Input(const std::string &name,
                      const unsigned &spriteId,
                      std::function<void(Button &)> callbackPressed,
                      std::function<void(Button &)> callbackHover,
                      std::function<void(Button &)> callbackUnHover,
                      engine::IScene &scene,
                      const pos_t &position = {0, 0});
                ~Input() = default;

                void manageEvents(const event_t &event) override;
                void display(sf::RenderWindow &window) override;
                const std::string &getText() const;
                Text &getTextComponent();


        private:
                bool _isClicked = false;
                Text _text;

        };
    }
}

#endif /* !INPUT_HPP_ */
