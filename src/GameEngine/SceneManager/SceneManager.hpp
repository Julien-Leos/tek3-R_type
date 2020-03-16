//
// Created by simon on 22/11/19.
//

#ifndef RTYPE_SCENEMANAGER_HPP
#define RTYPE_SCENEMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "IObject.hpp"
#include "IScene.hpp"
#include "ISceneManager.hpp"
#include "Throw.hpp"
#include "INetwork.hpp"

namespace rtype {
    namespace engine {
        class SceneManager : public ISceneManager {
            public:
                SceneManager(network::INetwork * network, sceneManagerType type);
                virtual ~SceneManager() = default;

                virtual void                                    draw(sf::RenderWindow &window) override;
                virtual void                                    update(const float &delta) override;
                virtual void                                    eventHandler(const event_t &event) override;

                virtual void                                    addScene(std::shared_ptr<IScene> newScene) override;

                virtual void                                    removeScene(const std::string &nameScene) override;
                virtual void                                    removeObjectOfScene(const std::string &nameScene, const std::string &nameObj) override;
                virtual void                                    removeObjectOfSceneById(const std::string &nameScene, const unsigned &id) override;
                virtual void                                    removeAllObjectsOfScene(const std::string &nameScene) override;

                virtual std::shared_ptr<IObject>                getObjectOfScene(const std::string &nameScene, const std::string &nameObj) const override;
                virtual std::shared_ptr<IObject>                getObjectByID(const std::string &nameScene, const unsigned &objectId) const override;
                virtual std::vector<std::shared_ptr<IObject> >  getAllObjectsOfScene(const std::string &nameScene) const override;

                virtual std::vector<std::shared_ptr<IScene> >   getScenes() const override;
                virtual std::shared_ptr<IScene>                 getScene(const std::string &name) const override;
                virtual network::INetwork *                     getNetwork(void) override;

                virtual size_t                                  getNewObjectId() override;
                bool                                            sceneExist(const std::string &name) override;
                bool                                            sceneExistAndHidden(const std::string &name) override;


                virtual const sceneManagerType &                getType() const override;
                virtual void                                    setType(const sceneManagerType &type) override;

                SoundManager                                    *getSoundManager() override;


        protected:
                network::INetwork *                     _network;
                SoundManager *                          _soundManager;

                std::vector<std::shared_ptr<IScene> >   _scenes;
                sceneManagerType                        _type;
                size_t                                  _nextId = 0;

        };
    }
}

#endif //RTYPE_SCENEMANAGER_HPP
