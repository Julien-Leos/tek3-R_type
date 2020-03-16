//
// Created by simon on 19/11/19.
//

#ifndef RTYPE_TEXT_HPP
#define RTYPE_TEXT_HPP

#include <Object.hpp>
#include <SFML/Graphics.hpp>
#include "IScene.hpp"

namespace rtype
{
    namespace engine
    {
        class Text : public Object
        {
        public:
            Text(const std::string &name,
                 const std::string text,
                 int fontSize,
                 const sf::Color &color,
                 IScene &scene,
                 const pos_t &position = {0, 0});

            ~Text() override;

            virtual void display(sf::RenderWindow &window);

            virtual void setText(const std::string &newText);

            virtual void changeColor(const sf::Color &color);

            virtual void changeSize(unsigned int &size);

            void setPosition(const pos_t &pos);

            const std::string &getText() const;
            sf::Text *getSfmlText();

        protected:
            std::string _text;
            int _fontSize;
            sf::Color _color;
            pos_t _position;
            sf::Text *_textSfml;
            sf::Font *_font;
        };
    }
}


#endif //RTYPE_TEXT_HPP
