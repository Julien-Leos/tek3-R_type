//
// Created by simon on 19/11/19.
//

#include "Text.hpp"

namespace rtype {
    namespace engine {
        Text::Text(const std::string &name,
                   const std::string text,
                   int fontSize,
                   const sf::Color &color,
                   IScene &scene,
                   const pos_t &position) :
                Object(name, 0, scene, position),
                _text(text),
                _fontSize(fontSize),
                _color(color),
                _position(position)
        {
            _font = new sf::Font();
            if (!_font->loadFromFile("assets/fonts/MetalArhythmetic.ttf"))
                EXCEPTION(std::runtime_error, "font not loaded entirely.");
            _textSfml = new sf::Text();
            _textSfml->setFont(*_font);
            _textSfml->setCharacterSize(_fontSize);
            _textSfml->setPosition(_position.x, _position.y);
            _textSfml->setFillColor(_color);
            _textSfml->setString(_text);
        }

        Text::~Text()
        {
/*    delete(_textSfml);
    delete(_font);*/
        }

        void Text::display(sf::RenderWindow &window)
        {
            window.draw(*_textSfml);
        }

        void Text::setText(const std::string &newText)
        {
            _text = newText;
            _textSfml->setString(_text);
        }

        const std::string &Text::getText() const
        {
            return _text;
        }

        void Text::changeColor(const sf::Color &color)
        {
            _textSfml->setFillColor(color);
        }

        void Text::changeSize(unsigned int &size)
        {
            _textSfml->setCharacterSize(size);
        }

        sf::Text *Text::getSfmlText()
        {
            return _textSfml;
        }

        void Text::setPosition(const pos_t &pos)
        {
            _position = pos;
            _textSfml->setPosition(pos.x, pos.y);
        }
    }
}