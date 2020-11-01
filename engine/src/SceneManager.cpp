//
// Created by mathi on 29/10/2020.
//

#include "SceneManager.hpp"

Engine::SceneManager Engine::SceneManager::_instance = Engine::SceneManager();

Engine::SceneManager::SceneManager() : _current(-1), _server(nullptr), _graph{} {};

Engine::SceneManager &Engine::SceneManager::get()
{
    return Engine::SceneManager::_instance;
}

Engine::AScene *Engine::SceneManager::getCurrent()
{
    auto res = Engine::SceneManager::_instance._scenes.find(Engine::SceneManager::_instance._current);

    if (res == Engine::SceneManager::_instance._scenes.end())
        return nullptr;
    return res->second;
}

void Engine::SceneManager::switchScene(int id)
{
    if (Engine::SceneManager::_instance._scenes.find(id) != Engine::SceneManager::_instance._scenes.end())
        Engine::SceneManager::_instance._current = id;
}

Engine::AScene *Engine::SceneManager::createScene(Engine::AScene *scene)
{
    Engine::SceneManager::_instance._scenes.insert(std::pair<int, Engine::AScene *>(scene->getId(), scene));
    return scene;
}

void Engine::SceneManager::setGraph(std::weak_ptr<Engine::AGraphical> graph)
{
    Engine::SceneManager::_instance._graph = std::move(graph);
}

void Engine::SceneManager::setServer(Engine::AServer *server)
{
    Engine::SceneManager::_instance._server = server;
}

std::shared_ptr<Engine::AGraphical> Engine::SceneManager::getGraph()
{
    if (Engine::SceneManager::_instance._graph.lock())
        return std::shared_ptr<Engine::AGraphical>(Engine::SceneManager::_instance._graph.lock());
    throw std::exception();
}

Engine::AServer *Engine::SceneManager::getServer()
{
    return Engine::SceneManager::_instance._server;
}
