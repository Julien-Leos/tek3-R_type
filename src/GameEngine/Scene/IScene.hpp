//
// Created by simon on 26/11/19.
//

#ifndef RTYPE_ISCENE_HPP
#define RTYPE_ISCENE_HPP

#include "IObject.hpp"
#include "Event.hpp"
#include "Communication.hpp"
#include "ISceneManager.hpp"

namespace rtype {
    namespace engine {
        class IObject;
        class ISceneManager;

        class IScene {
        public:
            virtual ~IScene() = default;

            virtual void display(sf::RenderWindow &window) = 0;
            virtual std::string getName() = 0;
            virtual void update(const float &actualTime) = 0;
            virtual void manageEvents(const event_t &event) = 0;
            virtual std::shared_ptr<IObject> getObject(const std::string &name) = 0;
            virtual std::shared_ptr<IObject> getObject(const unsigned &id) = 0;
            virtual std::shared_ptr<IObject> addObject(std::shared_ptr<IObject> newObject) = 0;
            virtual std::shared_ptr<IObject> addObject(const std::string &name,  const unsigned &spriteId, IScene &scene, const pos_t &position = {0, 0}) = 0;
            virtual std::shared_ptr<IObject> addObject(const std::string &name,  const unsigned &spriteId, const unsigned &objectId, IScene &scene, const pos_t &position = {0, 0}) = 0;
            virtual void removeObject(const std::string &name) = 0;
            virtual void removeObject(const unsigned &id) = 0;
            virtual void removeAllObjects() = 0;
            virtual std::vector<std::shared_ptr<IObject> > &getObjects() = 0;
            virtual rtype::engine::ISceneManager &getSceneManager() const = 0;
            virtual void setIsHidden(bool isHidden) = 0;
            virtual bool isIsHidden() const = 0;
        };
    }
}

#endif //RTYPE_ISCENE_HPP
