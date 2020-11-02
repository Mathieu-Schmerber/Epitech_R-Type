//
// Created by mathi on 29/10/2020.
//

#include "SceneManager.hpp"
#include "tools/Utils.hpp"

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
    if (Utils::isInMap(this->_scenes, this->_current))
        return this->_scenes[this->_current];
    // TODO: replace with a custom error exception
    throw std::exception(); //"SceneManager: No target scene"
}

void Engine::SceneManager::addScene(std::unique_ptr<Engine::AScene> scene)
{
    if (Utils::isInMap(this->_scenes, scene->getId()))
        std::cerr << "\033[33mScene WARNING : adding an already existing scene id, will overwrite its data (" << scene->getId() <<")\033[0m" << std::endl;
    this->_scenes[scene->getId()] = std::move(scene);
}

void Engine::SceneManager::switchScene(int id)
{
    if (Utils::isInMap(this->_scenes, id))
        this->_current = id;
    //TODO: else
    //TODO:     throw Error("No such scene of id: " + id);
}