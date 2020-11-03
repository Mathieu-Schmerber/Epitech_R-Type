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

void Engine::AScene::updateDeltatime(double delta)
{
    for (auto &sys : this->_systems)
        sys->setDeltatime(delta);
}

void Engine::AScene::addGroupAccess(const std::shared_ptr<Engine::AEntityGroup> &group)
{
    this->_groups.push_back(group);
    for (auto &e : group->getEntities())
        this->spawnEntity(e);
}

std::vector<std::shared_ptr<Engine::AEntityGroup>> Engine::AScene::getGroupAccess() const
{
    return this->_groups;
}

void Engine::AScene::onGroupUpdate(const std::shared_ptr<AEntityGroup> &group)
{
    if (Utils::isInVector(this->_groups, group)) {
        for (auto &e : group->getEntities()) {
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

void Engine::AScene::spawnEntity(std::shared_ptr<Entity> entity)
{
    this->_entities.push_back(std::move(entity));
    for (auto &sys : this->_systems) {
        if (this->_entities.back()->hasComponents(sys->getDependencies()))
            sys->addEntity(this->_entities.back());
    }
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