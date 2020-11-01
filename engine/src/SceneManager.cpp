//
// Created by mathi on 29/10/2020.
//

#include "SceneManager.hpp"

Engine::SceneManager::~SceneManager()
{
    this->_scenes.clear();
}

void Engine::SceneManager::handleSwitchRequests()
{
    int request;

    for (auto &entry : this->_scenes) {
        request = entry.second->getSwitchRequest();
        if (request != -1) {
            this->switchScene(request);
            entry.second->requestSwitch(-1);
        }
    }
}

std::unique_ptr<Engine::AScene> &Engine::SceneManager::getCurrent()
{
    auto it = this->_scenes.find(this->_current);

    if (it != this->_scenes.end())
        return it->second;
    // TODO: replace with a custom error exception
    throw std::exception("SceneManager: No target scene");
}

void Engine::SceneManager::addScene(std::unique_ptr<Engine::AScene> scene)
{
    auto it = this->_scenes.find(scene->getId());

    if (it == this->_scenes.end())
        this->_scenes[scene->getId()] = std::move(scene);
    //TODO: else
    //TODO:     throw Error("A scene of id: " + id + " already exists");
}

void Engine::SceneManager::switchScene(int id)
{
    auto it = this->_scenes.find(id);

    if (it != this->_scenes.end())
        this->_current = id;
    //TODO: else
    //TODO:     throw Error("No such scene of id: " + id);
}