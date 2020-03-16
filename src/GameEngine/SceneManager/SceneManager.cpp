//
// Created by simon on 22/11/19.
//

#include "SceneManager.hpp"

namespace rtype {
    namespace engine {

        SceneManager::SceneManager(network::INetwork * network, sceneManagerType type) : _network(network), _type(type)
        {
            if (getType() == CLIENT) {
                _soundManager = new SoundManager();
                _soundManager->addSong("assets/Sounds/buttonClicked.wav", "buttonClicked");
                _soundManager->addSong("assets/Sounds/ready.wav", "ready");
                _soundManager->addSong("assets/Sounds/welcomeToTheGame.wav", "welcomeToTheGame");
                _soundManager->addSong("assets/Sounds/roomCreated.wav", "roomCreated");
                _soundManager->addSong("assets/Sounds/enteringRoom.wav", "enteringRoom");
                _soundManager->addSong("assets/Sounds/logOut.wav", "logOut");
                _soundManager->addSong("assets/Sounds/bullet.wav", "bullet");
                _soundManager->addSong("assets/Sounds/rocket.wav", "rocket");
            }
        }

        void SceneManager::draw(sf::RenderWindow &window)
        {
            for (auto &e : _scenes) {
                if (!e->isIsHidden()) {
                    e->display(window);
                }
            }
        }

        void SceneManager::update(const float &delta)
        {
            for (auto &e : _scenes)
                if (!e->isIsHidden())
                    e->update(delta);
        }

        void SceneManager::addScene(std::shared_ptr<IScene> newScene)
        {
            _scenes.push_back(newScene);
        }

        void SceneManager::removeScene(const std::string &nameScene)
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1) {
                _scenes.erase(_scenes.begin() + pos);
            }
        }

        void SceneManager::removeObjectOfScene(const std::string &nameScene, const std::string &nameObj)
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                _scenes.at(pos)->removeObject(nameObj);
        }

        void SceneManager::removeObjectOfSceneById(const std::string &nameScene, const unsigned &id)
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                _scenes.at(pos)->removeObject(id);
        }

        void SceneManager::removeAllObjectsOfScene(const std::string &nameScene)
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                _scenes.at(pos)->removeAllObjects();
        }

        std::shared_ptr<IObject> SceneManager::getObjectOfScene(const std::string &nameScene, const std::string &nameObj) const
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                return _scenes.at(pos)->getObject(nameObj);
            EXCEPTION(std::runtime_error, nameScene + " scene doesn't exist.");
            return nullptr;
        }

        std::shared_ptr<IObject> SceneManager::getObjectByID(const std::string &nameScene, const unsigned &objectId) const
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                return _scenes.at(pos)->getObject(objectId);
            EXCEPTION(std::runtime_error, nameScene + " scene doesn't exist.");
            return nullptr;
        }

        std::vector<std::shared_ptr<IObject> > SceneManager::getAllObjectsOfScene(const std::string &nameScene) const
        {
            int pos = -1;
            unsigned int idx = 0;

            for (auto &e : _scenes) {
                if (e->getName() == nameScene) {
                    pos = idx;
                    break;
                }
                idx++;
            }
            if (pos != -1)
                return _scenes.at(pos)->getObjects();
            EXCEPTION(std::runtime_error, nameScene + " scene doesn't exist.");
            return {};
        }

        std::vector<std::shared_ptr<IScene> > SceneManager::getScenes() const
        {
            return _scenes;
        }

        std::shared_ptr<IScene>  SceneManager::getScene(const std::string &name) const
        {
            for (auto &i: _scenes) {
                if (i->getName() == name)
                    return i;
            }
            // TO-DO on a besoin de tester si la scene existe donc pas de EXXEPTION.
            // EXCEPTION(std::runtime_error, name + " scene doesn't exist.");
            return nullptr;
        }

        rtype::network::INetwork * SceneManager::getNetwork(void)
        {
            return _network;
        }

        void SceneManager::eventHandler(const event_t &event)
        {
            for (auto &e : _scenes) {
                if (e)
                    e->manageEvents(event);
            }
        }

        size_t SceneManager::getNewObjectId()
        {
            return _nextId++;
        }

        const ISceneManager::sceneManagerType &SceneManager::getType() const
        {
            return _type;
        }

        void SceneManager::setType(const ISceneManager::sceneManagerType &type)
        {
            _type = type;
        }

        bool SceneManager::sceneExist(const std::string &name)
        {
            for (auto &i: _scenes) {
                if (i->getName() == name)
                    return true;
            }
            return false;
        }

        bool SceneManager::sceneExistAndHidden(const std::string &name)
        {
            for (auto &i: _scenes) {
                if (i->getName() == name) {
                    if (i->isIsHidden())
                        return true;
                    return false;
                }
            }
            return true;
        }

        SoundManager *SceneManager::getSoundManager()
        {
            return _soundManager;
        }


    }
}