//
// Created by mathi on 29/10/2020.
//

#include "sceneManagement/SceneManager.hpp"
#include "tools/Utils.hpp"

Engine::SceneManager::~SceneManager()
{
    this->_scenes.clear();
    this->_groups.clear();
}

void Engine::SceneManager::parseRequest(const Engine::SceneRequest &request)
{
    switch (request.type()) {
        case QueryType::SWITCH_SCENE:
            for (auto &grp : this->getCurrent()->getGroupAccess())
                grp->freeze();
            this->switchScene(request.arguments().first);
            for (auto &grp : this->getCurrent()->getGroupAccess())
                grp->unFreeze();
            break;
        case QueryType::PUSH_TO_GROUP:
            this->addToGroup(request.arguments().first, request.arguments().second);
            for (auto &s : this->_scenes)
                s.second->onGroupUpdate(this->_groups[request.arguments().first]);
            break;
        default:
            break;
    }
}

void Engine::SceneManager::handleSceneRequests()
{
    for (auto &entry : this->_scenes) {
        for (auto &request : entry.second->getRequests())
            this->parseRequest(request);
        entry.second->clearRequests();
    }
}

void Engine::SceneManager::handleTime(double deltatime)
{
    for (auto &entry : this->_scenes)
        entry.second->updateDeltatime(deltatime);
}

// Groups

std::shared_ptr<Engine::AEntityGroup> Engine::SceneManager::addGroup(int id, const std::vector<std::shared_ptr<Engine::Entity>> &entities)
{
    if (!Utils::isInMap(this->_groups, id))
        this->_groups[id] = std::make_shared<Engine::AEntityGroup>();
    if (!entities.empty())
        this->_groups[id]->addEntities(entities);
    return this->_groups[id];
}

std::shared_ptr<Engine::AEntityGroup> Engine::SceneManager::addGroup(int id, std::shared_ptr<Engine::AEntityGroup> group)
{
    if (!Utils::isInMap(this->_groups, id))
        this->_groups[id] = std::move(group);
    return this->_groups[id];
}

void Engine::SceneManager::addToGroup(int id, std::shared_ptr<Engine::Entity> entity)
{
    if (!Utils::isInMap(this->_groups, id))
        this->addGroup(id, {entity});
    else
        this->_groups[id]->addEntity(entity);
}

void Engine::SceneManager::addToGroup(int id, std::vector<std::shared_ptr<Engine::Entity>> &entities)
{
    if (!Utils::isInMap(this->_groups, id))
        this->addGroup(id, entities);
    else
        this->_groups[id]->addEntities(entities);
}

void Engine::SceneManager::setAccessGroup(int scene, int group)
{
    if (Utils::isInMap(this->_scenes, scene) && Utils::isInMap(this->_groups, group))
        this->_scenes[scene]->addGroupAccess(this->_groups[group]);
}

void Engine::SceneManager::setAccessGroup(int scene, const std::vector<int> &groups)
{
    for (int group : groups) {
        if (Utils::isInMap(this->_scenes, scene) && Utils::isInMap(this->_groups, group))
            this->_scenes[scene]->addGroupAccess(this->_groups[group]);
    }
}

// Scenes

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