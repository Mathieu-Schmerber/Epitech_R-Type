//
// Created by mathi on 29/10/2020.
//

#include "AScene.hpp"

Engine::AScene::AScene(int id) : _sceneId(id) {}

Engine::AScene::~AScene()
{
    // Dtor
}

int Engine::AScene::getId() const
{
    return this->_sceneId;
}

void Engine::AScene::spawnEntity(std::unique_ptr<Entity> &entity)
{
    for (auto &sys : this->_systems) {
        if (entity->hasComponents(sys->getDependencies()))
            sys->addEntity(entity);
    }
}

void Engine::AScene::init()
{
    for (auto &entity : this->_entities)
        this->spawnEntity(entity);
}

void Engine::AScene::update()
{
    for (auto &sys : this->_systems)
        sys->update();
}