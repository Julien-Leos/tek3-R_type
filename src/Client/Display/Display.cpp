/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Display
*/

#include "guiGame.hpp"
#include "settings.hpp"
#include "Parallax.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Display.hpp"

namespace rtype {
    namespace graphics {
        Display::Display(const size_t &width, const size_t &height, const std::string &windowName, network::ClientNetwork * network)
                : _network(network), _width(width), _height(height), _name(windowName)
        {
            _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);
            _sceneManager = new engine::SceneManager(network, engine::SceneManager::CLIENT);
            _eventHandler = new client::EventHandler(*this);
        }

        Display::~Display()
        {
        }

        float Display::getTime()
        {
            sf::Time time = _clock.getElapsedTime();

            return static_cast<float>(time.asMilliseconds()) / 1000.0f;
        }

        void Display::restartClock()
        {
            _clock.restart();
        }

        void Display::init()
        {
            std::shared_ptr<rtype::client::Menu> menu = std::make_shared<client::Menu>("menu", *_sceneManager);
            std::shared_ptr<client::Parallax> parallax = std::make_shared<client::Parallax>("parallax", *_sceneManager);

            _eventHandler->initEvent();
            _window->setFramerateLimit(60);

            _sceneManager->addScene(parallax);
            _sceneManager->addScene(menu);
        }

        void Display::clear()
        {
            _window->clear(sf::Color::Black);
        }

        void Display::draw()
        {
            _sceneManager->draw(*_window);
        }

        void Display::display()
        {
            _window->display();
        }

        void Display::update()
        {
            _sceneManager->update(getTime());
        }

        void Display::run()
        {
            while (_window->isOpen()) {
                _network->poll();
                _eventHandler->handleEvent();
                clear();
                update();
                draw();
                display();
            }
        }

        engine::ISceneManager * Display::getSceneManager() const
        {
            return _sceneManager;
        }

        network::ClientNetwork * Display::getNetwork() const
        {
            return _network;
        }

        sf::RenderWindow * Display::getWindow() const
        {
            return _window;
        }
    }
}