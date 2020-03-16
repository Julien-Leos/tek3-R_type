/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ISceneManager
*/

#ifndef ISCENEMANAGER_HPP_
#define ISCENEMANAGER_HPP_

#include "IScene.hpp"
#include "IObject.hpp"
#include "INetwork.hpp"
#include "ClientNetwork.hpp"
#include "soundManager.hpp"

namespace rtype {
    namespace engine {
        class IScene;
        class IObject;
        class ISceneManager {
        public:

            enum sceneManagerType {
                CLIENT,
                SERVER
            };

            virtual ~ISceneManager() = default;

            virtual void                                    draw(sf::RenderWindow &window) = 0;
            virtual void                                    update(const float &delta) = 0;
            virtual void                                    eventHandler(const event_t &event) = 0;

            virtual void                                    addScene(std::shared_ptr<IScene> newScene) = 0;

            virtual void                                    removeScene(const std::string &nameScene) = 0;
            virtual void                                    removeObjectOfScene(const std::string &nameScene, const std::string &nameObj) = 0;
            virtual void                                    removeObjectOfSceneById(const std::string &nameScene, const unsigned &id) = 0;
            virtual void                                    removeAllObjectsOfScene(const std::string &nameScene) = 0;

            virtual std::shared_ptr<IObject>                getObjectOfScene(const std::string &nameScene, const std::string &nameObj) const = 0;
            virtual std::shared_ptr<IObject>                getObjectByID(const std::string &nameScene, const unsigned &objectId) const = 0;
            virtual std::vector<std::shared_ptr<IObject> >  getAllObjectsOfScene(const std::string &nameScene) const = 0;

            virtual std::vector<std::shared_ptr<IScene> >   getScenes() const = 0;
            virtual std::shared_ptr<IScene>                 getScene(const std::string &name) const = 0;
            virtual network::INetwork *                     getNetwork(void) = 0;
            virtual bool                                    sceneExist(const std::string &name) = 0;
            virtual bool                                    sceneExistAndHidden(const std::string &name) = 0;

            virtual size_t                                  getNewObjectId() = 0;

            virtual const sceneManagerType &                getType() const = 0;
            virtual void                                    setType(const sceneManagerType &type) = 0;
            virtual SoundManager *                    getSoundManager() = 0;

        };
    }
}

#endif /* !ISCENEMANAGER_HPP_ */
