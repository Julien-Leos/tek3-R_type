//
// Created by simon on 19/11/19.
//

#ifndef RTYPE_SCENE_HPP
#define RTYPE_SCENE_HPP


#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "IScene.hpp"

namespace rtype {
    namespace engine {

        class Scene : public IScene {
            protected:
                std::vector<std::shared_ptr<IObject> > _objects;
                std::vector<std::shared_ptr<IObject> > _toRemove;
                std::string                            _name;
                rtype::engine::ISceneManager & _sceneManager;
                bool                                   _isHidden;

            public:
                Scene(const std::string &name, rtype::engine::ISceneManager &sceneManager);
                virtual ~Scene();

                virtual void display(sf::RenderWindow &window) override ;
                virtual void update(const float &actualTime) override ;
                virtual void manageEvents(const event_t &event) override ;
                std::shared_ptr<IObject> getObject(const std::string &name) override ;
                std::shared_ptr<IObject> getObject(const unsigned &id) override ;
                std::shared_ptr<IObject> addObject(std::shared_ptr<IObject> newObject) override ;
                std::shared_ptr<IObject> addObject(const std::string &name, const unsigned &spriteId, IScene &scene, const pos_t &position = {0, 0}) override ;
                std::shared_ptr<IObject> addObject(const std::string &name, const unsigned &spriteId, const unsigned &objectId, IScene &scene, const pos_t &position = {0, 0}) override;
                void removeObject(const std::string &name) override ;
                void removeObject(const unsigned &id) override ;
                void removeAllObjects() override ;
                std::vector<std::shared_ptr<IObject> > &getObjects() override ;
                std::string getName() override;
                rtype::engine::ISceneManager &getSceneManager() const override;
                void setIsHidden(bool isHidden) override;
                bool isIsHidden() const override;
        };
    }
}


#endif //RTYPE_SCENE_HPP
