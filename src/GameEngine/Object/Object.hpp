/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <SFML/Window.hpp>
#include "IObject.hpp"
#include "IScene.hpp"
#include "Communication.hpp"
#include "AnimationComponent.hpp"
#include "MovementComponent.hpp"
#include "Event.hpp"

#define SPEED_X this->speed.first
#define SPEED_Y this->speed.second

#define POS_X this->position.first
#define POS_Y this->position.second

#define DEST_X this->destination.first
#define DEST_Y this->destination.second

#define GET_X(pair) pair.x
#define GET_Y(pair) pair.y

namespace rtype {
    namespace engine {
        class Object : public IObject {
            public:
                Object(const std::string &name, const unsigned &spriteId, IScene &scene, const pos_t &position = {0, 0});
                Object(const std::string &name, const unsigned &spriteId, const unsigned &objectId, IScene &scene, const pos_t &position = {0, 0});
                virtual ~Object();

                float               update(const float &actualTime) override;
                void                display(sf::RenderWindow &window) override;
                const unsigned &    getId() const override;
                const std::string & getName() const override;
                void                manageEvents(const event_t &event) override;
                void                collide(std::shared_ptr<IObject> other) override;
                void                eventReachedDestination() override;
                void                eventHit(std::shared_ptr<IObject> other) override;
                IScene &            getScene() const override;
                bool                isHidden() const override;
                void                setHidden(bool hidden) override;

            protected:
                std::string         _name = "";
                IScene &            _scene;
                bool                _hidden = false;
                unsigned            _objectId = 0;
                float               _oldTime = 0;
        };
    }
}

#endif /* !OBJECT_HPP_ */
