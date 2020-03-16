/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "IDisplay.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "ClientNetwork.hpp"
#include "EventHandler.hpp"

namespace rtype {
    namespace graphics {
        class Display : public IDisplay {
            public:
                Display(const size_t &width, const size_t &height, const std::string &windowName, network::ClientNetwork *network);
                ~Display();
                void                    init() override;
                void                    run() override;
                void                    display() override;
                void                    update() override;
                void                    draw() override;
                void                    clear() override;
                float                   getTime() override;
                void                    restartClock() override;

                engine::ISceneManager * getSceneManager() const override;
                sf::RenderWindow *      getWindow() const override;

                network::ClientNetwork * getNetwork() const override;
                
            private:
                rtype::engine::SceneManager *   _sceneManager;
                sf::RenderWindow *              _window;

                network::ClientNetwork *        _network;
                client::EventHandler *          _eventHandler;

                size_t                      _width;
                size_t                      _height;
                std::string                 _name;
                sf::Clock                   _clock;
        };
    }
}

#endif /* !DISPLAY_HPP_ */
