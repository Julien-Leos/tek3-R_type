//
// Created by simon on 01/12/19.
//

#include "Menu.hpp"
#include "guiGame.hpp"

std::vector<std::shared_ptr<rtype::engine::Button>> rtype::client::GuiGame::getButtons() const
{
    return _buttons;
}

void rtype::client::GuiGame::setButtons(const std::vector<std::shared_ptr<rtype::engine::Button>> &buttons)
{
    _buttons = buttons;
}

std::vector<std::shared_ptr<rtype::engine::Text>> rtype::client::GuiGame::getTexts() const
{
    return _texts;
}

void rtype::client::GuiGame::setTexts(const std::vector<std::shared_ptr<rtype::engine::Text>> &texts)
{
    _texts = texts;
}

unsigned int rtype::client::GuiGame::getLife() const
{
    return _life;
}

void rtype::client::GuiGame::setLife(unsigned int life)
{
    _life = life;
}

unsigned int rtype::client::GuiGame::getScore() const
{
    return _score;
}

void rtype::client::GuiGame::setScore(unsigned int score)
{
    _score = score;
}

const std::string &rtype::client::GuiGame::getUsername() const
{
    return _username;
}

void rtype::client::GuiGame::setUsername(const std::string &username)
{
    _username = username;
}

rtype::client::GuiGame::GuiGame(const std::string &name, rtype::engine::ISceneManager &sceneManager,
                                const std::string &username)  : Scene(name,sceneManager), _username(username)
{
    _life = 3;
    _score = 0;


    std::shared_ptr<rtype::engine::Object> footer = std::make_shared<rtype::engine::Object>("footer",
                                                                                            59,
                                                                                            *this,
                                                                                            pos_t({0, 20}));

    this->addObject(footer);
    footer->getComponent<engine::MovementComponent>()->setPosition(0, 20);

    std::shared_ptr<rtype::engine::Object> life = std::make_shared<rtype::engine::Object>("life",
                                                                                          60,
                                                                                          *this,
                                                                                          pos_t({180, 820}));

    this->addObject(life);
    life->getComponent<engine::MovementComponent>()->setPosition(180, 820);

    std::shared_ptr<rtype::engine::Text> usernamePlayer = std::make_shared<rtype::engine::Text>(
            "username",
            _username,
            80,
            sf::Color(sf::Color::White),
            *this,
            pos_t({1600/2-300,0}));

    //center text
    sf::FloatRect textRect = usernamePlayer->getSfmlText()->getLocalBounds();
    usernamePlayer->getSfmlText()->setOrigin(textRect.left + textRect.width/2.0f,
                                             textRect.top  + textRect.height/2.0f);
    usernamePlayer->getSfmlText()->setPosition(sf::Vector2f(1600/2.0f,860));

    std::shared_ptr<engine::Text> scorePlayer = std::make_shared<engine::Text>(
            "score",
            "Score: " + std::to_string(_score),
            70,
            sf::Color(sf::Color::White),
            *this,
            pos_t({20,20})
    );
    //center text
    sf::FloatRect textRectScore = scorePlayer->getSfmlText()->getLocalBounds();
    scorePlayer->getSfmlText()->setOrigin(textRectScore.left + textRectScore.width/2.0f,
                                          textRectScore.top  + textRectScore.height/2.0f);
    scorePlayer->getSfmlText()->setPosition(sf::Vector2f(1300,860));

    _texts.push_back(usernamePlayer);
    _texts.push_back(scorePlayer);
    for (auto &e : _texts) {
        this->addObject(e);
    }
}

void rtype::client::GuiGame::update(const float &actualTime)
{
    static unsigned int oldScore = this->getScore();
    static unsigned int oldLife = this->getLife();

    if (oldScore != _score) {
        oldScore = _score;
        std::static_pointer_cast<engine::Text>(this->getObject("score"))->setText("Score : " + std::to_string(_score));
    }
    if (oldLife != _life) {
        oldLife = _life;
        if (_life == 1) {
            this->getObject("life")->getComponent<engine::AnimationComponent>()->goNextSprite();
        } else if (_life == 2) {
            this->getObject("life")->getComponent<engine::AnimationComponent>()->goNextSprite();
        }
    }
    if (_isHidden)
        return;
    for (auto &e : _objects)
        if (e)
            e->update(actualTime);
}
