/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Input
*/

#include "Input.hpp"

namespace rtype {
    namespace engine {
        Input::Input(const std::string &name,
            const unsigned &spriteId,
            std::function<void(Button &)> callbackPressed,
            std::function<void(Button &)> callbackHover,
            std::function<void(Button &)> callbackUnHover,
            engine::IScene &scene,
            const pos_t &position)
        : Button(name, spriteId, callbackPressed, callbackHover, callbackUnHover, scene, position),
        _text(Text("inputText", "", 32, sf::Color::Red, scene, {position.x + 15, position.y + 15}))
        {
        }

        void Input::display(sf::RenderWindow &window)
        {
            window.draw(getComponent<AnimationComponent>()->getSprite());
            window.draw(*_text.getSfmlText());
        }

        void Input::manageEvents(const event_t &event)
        {
            Button::manageEvents(event);

            std::string str = "";
            std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

            for (auto &i: event.keyRelease) {
                if (!i.second)
                    continue;
                if (i.first >= Key::A && i.first <= Key::Num9 && _isClicked && _text.getText().size() < 15 && _text.getSfmlText()->getString().getSize() <= 9) { // i.first >= 0 && i.first <= 35
                    str = _text.getText();
                    _text.setText(str + alphabet[i.first]); // append new character to string
                } else if (i.first == Key::Space && _isClicked && _text.getText().size() < 15 && _text.getSfmlText()->getString().getSize() <= 9) {
                    str = _text.getText();
                    _text.setText(str + " ");
                } else if (i.first == Key::BackSpace && _isClicked) {
                    str = _text.getText();
                    _text.setText(str.substr(0, str.length() - 1));
                }
            }
            if (event.mouseButtonPressed.find(MouseButton::MouseLeft)->second) {
                if (!getComponent<AnimationComponent>()
                ->getSprite()
                .getGlobalBounds()
                .contains(event.mousePosition.first, event.mousePosition.second)) { // click outside the input
                    getComponent<AnimationComponent>()->changeSprite(19);
                    _isClicked = false;
                } else  {
                    getComponent<AnimationComponent>()->changeSprite(20);
                    _isClicked = true;
                }
            }
        }

        Text &Input::getTextComponent()
        {
            return _text;
        }

        const std::string &Input::getText() const
        {
            return _text.getText();
        }
    }
}