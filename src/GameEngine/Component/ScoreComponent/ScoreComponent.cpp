/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ScoreComponent
*/

#include "ScoreComponent.hpp"

namespace rtype {
namespace engine {

ScoreComponent::ScoreComponent(engine::IObject &owner) : Component(owner)
{
}

int  ScoreComponent::getScore() const
{
    return _score;
}

void ScoreComponent::setScore(int score)
{
    _score = score;
}

void ScoreComponent::addScore(int toAdd)
{
    _score += toAdd;
}

void ScoreComponent::removeScore(int toRemove)
{
    _score -= toRemove;
}

}
}
