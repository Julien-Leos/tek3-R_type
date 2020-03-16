/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AnimationComponent
*/

#include "AnimationComponent.hpp"


namespace rtype {
    namespace engine {

AnimationComponent::AnimationComponent(IObject &object, const unsigned &spriteId)
: Component(object), _spriteId(spriteId)
{
    _texture = std::make_shared<sf::Texture>();
    _sprite = std::make_shared<sf::Sprite>();
    changeSprite(spriteId);
}

void AnimationComponent::update(const float &delta)
{
    if (_owner.getScene().getSceneManager().getType() == engine::ISceneManager::SERVER)
        return;
    if (isAnimated()) {
        if (_remainingTime <= 0) {
            _remainingTime = _animationSpeed;
            goNextSprite();
        } else {
            _remainingTime -= delta;
        }
    }
}

sf::Sprite &AnimationComponent::getSprite() const
{
    return *_sprite;
}

const size_t &AnimationComponent::getActual() const
{
    return _actual;
}

const std::pair<float, float> &AnimationComponent::getSize() const
{
    return _size;
}

bool AnimationComponent::isAnimated() const
{
    return _animationSpeed != 0 && (_nbLoop != 0 || _infiniteLoop == true);
}

void AnimationComponent::setAnimationSpeed(const float &speed)
{
    _animationSpeed = speed;
    _remainingTime = speed;
}

void AnimationComponent::setNbLoop(const float &nbLoop)
{
    _nbLoop = nbLoop;
}

void AnimationComponent::setInfiniteLoop(const bool &state)
{
    _infiniteLoop = state;
}

void AnimationComponent::goNextSprite()
{
    int col = 0;
    int row = 0;

    if (_actual == _spriteSheetSize - 1) {
        if (!_infiniteLoop && _nbLoop != 0)
            _nbLoop--;
        if (_boomerang) {
            _actual--;
            if (_actual == 0)
                _boomerangGoingBack = false;
            else
                _boomerangGoingBack = true;
        } else if (_infiniteLoop || _nbLoop > 0)
            _actual = 0;
    } else {
        if (_boomerang && _boomerangGoingBack)
            _actual--;
        else
            _actual++;
    }
    col = _actual % _nbCols;
    row = _actual / _nbCols;
    _sprite->setTextureRect(sf::IntRect(_size.first * col + _initialPos.first, _size.second * row + _initialPos.second, _size.first, _size.second));
}

void AnimationComponent::changeSprite(const unsigned &spriteId)
{
    if (spriteId == 0) {
        *_texture = sf::Texture();
        *_sprite = sf::Sprite();
        return;
    }

    std::ifstream jsonFile("config/sprites.json");
    boost::property_tree::ptree pt;
    std::string filepath;

    read_json(jsonFile, pt);
    pt = pt.get_child(std::to_string(spriteId));
    if (pt.empty())
        EXCEPTION(std::runtime_error, "load this sprite ID: " + std::to_string(spriteId) + " Failed");
    _nbRows = pt.get<size_t>("nbRows");
    _nbCols = pt.get<size_t>("nbCols");
    _spriteSheetSize = _nbCols * _nbRows;

    setAnimationSpeed(pt.get<float>("animationSpeed"));
    setNbLoop(pt.get<int>("animationLoop"));
    setInfiniteLoop(pt.get<bool>("infiniteLoop"));
    _boomerang = pt.get<bool>("boomerang");

    _size.first = pt.get<float>("size.x");
    _size.second = pt.get<float>("size.y");

    _initialPos.first = pt.get<float>("position.x");
    _initialPos.second = pt.get<float>("position.y");

    filepath = pt.get<std::string>("filepath");
    if (!_texture->loadFromFile(filepath))
        EXCEPTION(std::runtime_error, "load: " + filepath + " Failed");
    _sprite->setTexture(*_texture);
    _sprite->setTextureRect(sf::IntRect(_initialPos.first, _initialPos.second, _size.first, _size.second));
}

void AnimationComponent::goToSprite(const size_t &index)
{
    int col = 0;
    int row = 0;

    if (index < _spriteSheetSize) {
        _actual = index;
        col = _actual % _nbCols;
        row = _actual / _nbCols;
        _sprite->setTextureRect(sf::IntRect(_size.first * col + _initialPos.first, _size.second * row + _initialPos.second, _size.first, _size.second));
    }
}

void AnimationComponent::setSize(const float & x, const float & y)
{
    _size.first = x;
    _size.second = y;
}

unsigned AnimationComponent::getSpriteId(void)
{
    return _spriteId;
}

}
}
