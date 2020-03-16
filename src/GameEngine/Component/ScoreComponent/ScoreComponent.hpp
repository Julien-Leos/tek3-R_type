/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ScoreComponent
*/

#ifndef SCORECOMPONENT_HPP_
#define SCORECOMPONENT_HPP_

#include "Component.hpp"
#include "IObject.hpp"
#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"

namespace rtype {
namespace engine {
    class ScoreComponent : public engine::Component {
        public:
            ScoreComponent(engine::IObject &parent);
            ~ScoreComponent() = default;

            int getScore() const;
            void setScore(int score);
            void addScore(int toAdd);
            void removeScore(int toRemove);

        private:
            int _score = 0;
    };
}
}

#endif /* !SCORECOMPONENT_HPP_ */
