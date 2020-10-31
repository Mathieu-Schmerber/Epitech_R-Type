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

void Engine::AScene::spawnEntity(std::unique_ptr<Entity> entity)
{
    std::cout << "systems" << std::endl;
    for (auto &sys : this->_systems) {
        if (entity->hasComponents(sys->getDependencies()))
            sys->addEntity(entity);
    }
    this->_entities.push_back(std::move(entity));
}

void Engine::AScene::update()
{
    for (auto &sys : this->_systems)
        sys->update();
}