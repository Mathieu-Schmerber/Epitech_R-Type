//
// Created by mathi on 06/11/2020.
//

#include "scenes/SceneType.hpp"
#include "scenes/InGame.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "systems/ClientNetworkSystem.hpp"
#include "entities/Music.hpp"

InGame::InGame(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
: _window(window), _events(events), _server(server), Engine::AScene(SceneType::GAME)
{
    this->initEntities();
    this->initSystems();
}

void InGame::initEntities()
{
// TODO: create leave game button
}

void InGame::initSystems()
{
    auto scene = std::shared_ptr<Engine::AScene>(this);
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto music = std::make_unique<Engine::MusicSystem>();
    auto network = std::make_unique<ClientNetworkSystem>(this->_server, this->_events, scene);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(network));
}

void InGame::onFocus() {}

void InGame::onExit()
{
    this->_entities.clear();
}