//
// Created by mathi on 29/10/2020.
//

#include "AScene.hpp"

Engine::AScene::AScene(int id) : _sceneId(id), _sceneSwitchRequest(-1) {}

Engine::AScene::~AScene()
{
    this->_entities.clear();
    this->_systems.clear();
}

int Engine::AScene::getId() const
{
    return this->_sceneId;
}

void Engine::AScene::spawnEntity(std::shared_ptr<Entity> entity)
{
    this->_entities.push_back(std::move(entity));
    for (auto &sys : this->_systems) {
        if (this->_entities.back()->hasComponents(sys->getDependencies()))
            sys->addEntity(this->_entities.back());
    }
}

int Engine::AScene::getSwitchRequest() const
{
    return this->_sceneSwitchRequest;
}

void Engine::AScene::requestSwitch(int scene)
{
    this->_sceneSwitchRequest = scene;
}

void Engine::AScene::update()
{
    for (auto &sys : this->_systems)
        sys->update();
}

void Engine::AScene::initSystems() {

}

void Engine::AScene::initEntities() {

}