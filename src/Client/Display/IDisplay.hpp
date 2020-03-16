/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "ISceneManager.hpp"

namespace rtype {
namespace graphics {

class IDisplay {
    #define WINDOW_WIDTH 1600
    #define WINDOW_HEIGHT 900

	public:
                virtual void                    init() = 0;
                virtual void                    run() = 0;
                virtual void                    display() = 0;
                virtual void                    update() = 0;
                virtual void                    draw() = 0;
                virtual void                    clear() = 0;
                virtual float                   getTime() = 0;
                virtual void                    restartClock() = 0;

                virtual engine::ISceneManager * getSceneManager() const = 0;
                virtual sf::RenderWindow *      getWindow() const = 0;

                virtual network::ClientNetwork * getNetwork() const = 0;
};

}
}

#endif /* !IDISPLAY_HPP_ */
