//
// Created by simon on 26/11/19.
//

#include "Parallax.hpp"

namespace rtype {
namespace client {
Parallax::Parallax(const std::string &name, rtype::engine::ISceneManager &sceneManager) : Scene(name, sceneManager)
{
    std::shared_ptr<ParallaxObject> obj1 = std::make_shared<ParallaxObject>("bg1", 4, *this, pos_t({0, 0}), pos_t({0, 0}), pos_t({-1600, 0}), 22);
    std::shared_ptr<ParallaxObject> obj2 = std::make_shared<ParallaxObject>("bg2", 5, *this, pos_t({0, 0}), pos_t({0, 0}), pos_t({-1600, 0}), 18);
    std::shared_ptr<ParallaxObject> obj3 = std::make_shared<ParallaxObject>("bg3", 6, *this, pos_t({0, 0}), pos_t({0, 0}), pos_t({-1600, 0}), 12);

    this->addObject(obj1);
    obj1->setDestination({-1600, 0}, 20);

    this->addObject(obj2);
    obj2->setDestination({-1600, 0}, 15);

    this->addObject(obj3);
    obj3->setDestination({-1600, 0}, 10);
}

Parallax::~Parallax()
{
}

ParallaxObject::ParallaxObject(const std::string &name,
                                              const unsigned int &spriteId,
                                              engine::IScene &scene,
                                              const pos_t &position,
                                              const pos_t &restartPos,
                                              const pos_t &reachedDestination,
                                              const unsigned &speed
) : Object(name, spriteId, scene, position), _restartDestination(restartPos), _reachedDestination(reachedDestination), _speed(speed)
{
}

void ParallaxObject::eventReachedDestination()
{
    this->getComponent<rtype::engine::MovementComponent>()->setPosition(_restartDestination.x, _restartDestination.y);
    this->setDestination(_reachedDestination, _speed);
}

void ParallaxObject::setDestination(const pos_t &reachedDestination, const unsigned &speed)
{
    this->getComponent<rtype::engine::MovementComponent>()->setDestination({reachedDestination.x, reachedDestination.y}, speed);
}
}
}