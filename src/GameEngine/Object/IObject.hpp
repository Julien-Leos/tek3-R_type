/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include <iostream>
#include <memory>
#include <typeindex>
#include "IScene.hpp"
#include "Communication.hpp"
#include "Event.hpp"
#include "IComponent.hpp"
#include "Throw.hpp"

namespace rtype {
    namespace engine {
        class IScene;
        class IComponent;
        class IObject {
        public:
            virtual ~IObject() = default;
            virtual float               update(const float &actualTime) = 0;
            virtual void                display(sf::RenderWindow &window) = 0;
            virtual const unsigned &    getId() const = 0;
            virtual const std::string & getName() const = 0;
            virtual void                manageEvents(const event_t &event) = 0;
            virtual void                collide(std::shared_ptr<IObject> other) = 0;
            virtual void                eventHit(std::shared_ptr<IObject> other) = 0;
            virtual void                eventReachedDestination() = 0;
            virtual IScene &            getScene() const = 0;
            virtual bool                isHidden() const = 0;
            virtual void                setHidden(bool hidden) = 0;

            template<class T>
            void addComponent(std::shared_ptr<T> component)
            {
                auto it = _components.find(typeid(T));

                if (it == _components.end())
                    _components[typeid(T)] = component;
            }

            template<class T>
            std::shared_ptr<T> getComponent()
            {
                auto it = _components.find(typeid(T));

                if (it != _components.end())
                    return std::static_pointer_cast<T>(it->second);
                return nullptr;
            }

        protected:
            std::map<std::type_index, std::shared_ptr<IComponent>> _components;
        };
    }
}

#endif /* !IOBJECT_HPP_ */
