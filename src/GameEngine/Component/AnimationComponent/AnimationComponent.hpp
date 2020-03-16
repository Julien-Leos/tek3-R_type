/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AnimationComponent
*/

#ifndef ANIMATIONCOMPONENT_HPP_
#define ANIMATIONCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "IObject.hpp"
#include "Component.hpp"
#include "Throw.hpp"

namespace rtype {
    namespace engine {
        class AnimationComponent : public Component {
            public:
                AnimationComponent(IObject &parent, const unsigned &spriteId);
                virtual ~AnimationComponent() = default;

                void                                    update(const float &delta) override;
                sf::Sprite &                            getSprite() const;
                const std::pair<float, float> &         getSize() const;
                bool                                    isAnimated() const;
                void                                    setAnimationSpeed(const float &speed);
                void                                    setNbLoop(const float &nbLoop);
                void                                    setInfiniteLoop(const bool &state);
                void                                    goNextSprite();
                void                                    goToSprite(const size_t &index);
                const size_t &                          getActual(void) const;
                void                                    changeSprite(const unsigned &spriteId);

                void                                    setSize(const float & x, const float & y);
                unsigned                                getSpriteId(void);

            protected:
                size_t                          _actual = 0;
                size_t                          _nbRows = 0;
                size_t                          _nbCols = 0;
                size_t                          _spriteSheetSize = 0;
                float                           _animationSpeed = 0;
                float                           _remainingTime = 0;
                size_t                          _nbLoop = 0;
                bool                            _infiniteLoop = false;
                bool                            _boomerang = false;
                bool                            _boomerangGoingBack = false;
                unsigned                        _spriteId = 0;
                std::pair<float, float>         _size = {0, 0};
                std::pair<float, float>         _initialPos = {0, 0};
                std::shared_ptr<sf::Sprite>     _sprite;
                std::shared_ptr<sf::Texture>    _texture;
        };

    }
}

#endif /* !ANIMATIONCOMPONENT_HPP_ */
