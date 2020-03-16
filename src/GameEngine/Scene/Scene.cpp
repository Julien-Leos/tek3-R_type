//
// Created by simon on 19/11/19.
//

#include <chrono>
#include "Scene.hpp"

namespace rtype {
    namespace engine {
Scene::Scene(const std::string &name, ISceneManager &sceneManager)
: _name(name), _sceneManager(sceneManager), _isHidden(false)
{
}

Scene::~Scene()
{
}

void Scene::display(sf::RenderWindow &window)
{
    if (_isHidden)
        return;
    for (auto &e : _objects)
        if (e && !e->isHidden())
            e->display(window);
}

void Scene::update(const float &actualTime)
{
    int pos = 0;

    if (_isHidden)
        return;

    for (auto &e : _objects) {
        try {
            if (e && !e->isHidden())
                e->update(actualTime);
        } catch (std::exception &exception) {
            continue;
        }
    }
    for (auto &e : _toRemove) {
        pos = 0;
        for (auto &i: _objects) {
            if (i->getId() == e->getId()) {
                _objects.erase(_objects.begin() + pos);
                break;
            }
            pos++;
        }
    }
    _toRemove.clear();
} 

void Scene::manageEvents(const event_t &event)
{
    if (_isHidden)
        return;
    for (auto &e : _objects) {
        if (e && !e->isHidden())
            e->manageEvents(event);
    }
}

std::shared_ptr<IObject> Scene::getObject(const std::string &name)
{
    for (auto &e : _objects) {
        if (e->getName() == name)
            return e;
    }
    return nullptr;
}

std::shared_ptr<IObject> Scene::getObject(const unsigned &id)
{
    for (auto &e : _objects) {
        if (e->getId() == id) {
            return e;
        }
    }
    return nullptr;
}

std::shared_ptr<IObject> Scene::addObject(std::shared_ptr<IObject> newObject)
{
    _objects.push_back(newObject);
    return newObject;
}

std::shared_ptr<IObject> Scene::addObject(const std::string &name,  const unsigned &spriteId, IScene &scene, const pos_t &position)
{
    std::shared_ptr<Object> tmpObj = std::make_shared<Object>(name, spriteId, scene, position);
    _objects.push_back(tmpObj);
    return tmpObj;
}

std::shared_ptr<rtype::engine::IObject> rtype::engine::Scene::addObject(const std::string &name,  const unsigned &spriteId, const unsigned &objectId, IScene &scene, const pos_t &position)
{
    std::shared_ptr<Object> tmpObj = std::make_shared<Object>(name, spriteId, objectId, scene, position);
    _objects.push_back(tmpObj);
    return tmpObj;
}

void rtype::engine::Scene::removeObject(const std::string &name)
{
    int pos = 0;

    for (auto &e : _objects) {
        if (e && e->getName() == name)
            _toRemove.push_back(e);
            // _objects.erase(_objects.begin() + pos);
        pos++;
    }
}

void Scene::removeObject(const unsigned &id)
{
    int pos = 0;

    for (auto &e : _objects) {
        if (e && e->getId() == id)
            _toRemove.push_back(e);
            // _objects.erase(_objects.begin() + pos);
        pos++;
    }
}

void Scene::removeAllObjects()
{
    for (auto &e: _objects)
        removeObject(e->getId());
}

std::vector <std::shared_ptr<IObject> > &Scene::getObjects()
{
    return _objects;
}

std::string Scene::getName()
{
    return _name;
}

ISceneManager &Scene::getSceneManager() const
{
    return _sceneManager;
}

bool Scene::isIsHidden() const
{
    return _isHidden;
}

void Scene::setIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}
}
}
