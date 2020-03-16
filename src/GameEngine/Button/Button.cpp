#include <utility>

//
// Created by simon on 20/11/19.
//
#include <utility>
#include "Button.hpp"


namespace rtype {
    namespace engine {

Button::Button(const std::string &name,
                            const unsigned &spriteId,
                            std::function<void(Button &)> callbackPressed,
                            std::function<void(Button &)> callbackHover,
                            std::function<void(Button &)> callbackUnHover,
                            IScene &scene,
                            const pos_t &position) : Object(name, spriteId, scene, position),
                                                    _buttonPos(position),
                                                    _spriteId(spriteId),
                                                    _isHover(false),
                                                    _mPressedCallback(callbackPressed), _mHoverCallback(callbackHover), _mUnHoverCallback(callbackUnHover)
{
}

Button::~Button()
{
}


void Button::manageEvents(const event_t &event)
{
    sf::Vector2f mousePos = {event.mousePosition.first, event.mousePosition.second};

    if (this->getComponent<AnimationComponent>()->getSprite().getGlobalBounds().contains(mousePos) && _mHoverCallback != nullptr) {
        if (!_isHover)
            _mHoverCallback(*this);
        _isHover = true;
    } else {
        if (_isHover)
            _mUnHoverCallback(*this);
        _isHover = false;
    }
    if (event.mouseButtonPressed.find(MouseLeft)->second) {
        if (this->getComponent<AnimationComponent>()->getSprite().getGlobalBounds().contains(mousePos) && _mPressedCallback != nullptr)
            _mPressedCallback(*this);
    }
}

const unsigned &Button::getSpriteId()
{
    return _spriteId;
}

void Button::setCallbackHover(std::function<void(Button & )> &callback)
{
    _mHoverCallback = callback;
}

void Button::setCallbackUnHover(std::function<void(Button & )> &callback)
{
    _mUnHoverCallback = callback;
}

void Button::setCallBackButton(std::function<void(Button & )> &callback)
{
    _mPressedCallback = callback;
}

const pos_t &Button::getButtonPos() const
{
    return _buttonPos;
}

void Button::callPressed()
{
    if (_mPressedCallback)
        this->_mPressedCallback(*this);
}

void Button::callHover()
{
    if (_mHoverCallback)
        this->_mHoverCallback(*this);
}

void Button::callUnHover()
{
    if (_mUnHoverCallback)
        this->_mUnHoverCallback(*this);
}
    }
}