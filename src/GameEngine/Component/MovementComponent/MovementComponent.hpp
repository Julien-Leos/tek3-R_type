/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Movementcomponent
*/

#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include <iostream>
#include "IObject.hpp"
#include "AnimationComponent.hpp"
#include "IComponent.hpp"

namespace rtype {
    namespace engine {
        class IObject;

        class MovementComponent : public Component {
            public:
                MovementComponent(IObject &object);
                ~MovementComponent() = default;

                void                            update(const float &delta) override;
                bool                            hasReachDuration(const float &delta);
                bool                            isMoving() const;
                bool                            isFreeMoving() const;
                bool                            isBlocking() const;
                void                            setSpeed(const float &x, const float &y);
                void                            setPosition(const float &x, const float &y);
                void                            setFreeMoving(const bool &state);
                void                            setBlocking(const bool &state);
                void                            setDestination(const std::pair<float, float> &newDest, const float &timeToReach);
                const pos_t &                   getPosition() const;
                const std::pair<float, float> & getSpeed() const;
                const std::pair<float, float> & getDestination() const;
                bool                            willColide(const float &delta, std::shared_ptr<IObject> other) const;

            protected:
                bool                        _freeMoving = false;
                bool                        _blocking = false;
                float                       _remainingTimeMoving = 0;
                std::pair<float, float>     _speed{0.0, 0.0};
                pos_t                        _position{0.0, 0.0};
                std::pair<float, float>     _destination{0.0, 0.0};
        };

    }
}

#endif /* !MOVEMENTCOMPONENT_HPP_ */
