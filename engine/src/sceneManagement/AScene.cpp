//
// Created by mathi on 29/10/2020.
//

#include "sceneManagement/AScene.hpp"
#include "tools/Utils.hpp"

Engine::AScene::AScene(int id) : _sceneId(id) {}

Engine::AScene::~AScene()
{
    this->_entities.clear();
    this->_systems.clear();
}

void Engine::AScene::updateDeltatime(float delta)
{
    for (auto &sys : this->_systems)
        sys->setDeltatime(delta);
}

void Engine::AScene::addGroupAccess(int id, const std::shared_ptr<Engine::AEntityGroup> &group)
{
    this->_groups[id] = group;
    for (auto &e : group->getEntities())
        this->spawnEntity(e);
}

std::map<int, std::shared_ptr<Engine::AEntityGroup>> Engine::AScene::getGroupAccess() const
{
    return this->_groups;
}

void Engine::AScene::onGroupUpdate(int id)
{
    if (Utils::isInMap(this->_groups, id)) {
        for (auto &e : this->_groups[id]->getEntities()) {
            if (!Utils::isInVector(this->_entities, e))
                this->spawnEntity(e);
        }

    }
}

void Engine::AScene::clearRequests()
{
    this->_requests.clear();
}

std::vector<Engine::SceneRequest> Engine::AScene::getRequests() const
{
    return this->_requests;
}

void Engine::AScene::pushRequest(const SceneRequest &request)
{
    this->_requests.push_back(request);
}

int Engine::AScene::getId() const
{
    return this->_sceneId;
}

void Engine::AScene::spawnEntity(std::shared_ptr<Entity> &entity)
{
    this->_entities.push_back(std::move(entity));
    for (auto &sys : this->_systems) {
        if (this->_entities.back()->hasComponents(sys->getDependencies()))
            sys->addEntity(this->_entities.back());
    }
}

void Engine::AScene::despawnEntity(std::shared_ptr<Entity> &entity)
{
    for (auto &sys : this->_systems) {
        if (entity->hasComponents(sys->getDependencies()))
            sys->deleteEntity(entity);
    }
    Utils::removeFromVector(this->_entities, entity);
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