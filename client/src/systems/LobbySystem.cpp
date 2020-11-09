//
// Created by mathi on 09/11/2020.
//

#include "components/LobbyComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "systems/LobbySystem.hpp"

LobbySystem::LobbySystem(std::shared_ptr<NetworkAccess> &server, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<Engine::AScene> &scene)
: _server(server), _events(events), _scene(scene), Engine::System()
{
    this->addDependency<LobbyComponent>();
    this->addDependency<Engine::ClickableComponent>();
}

void LobbySystem::updateFromServer()
{
    auto &tcp = this->_server->getTcpSocket();
}

void LobbySystem::handleScroll()
{
    // TODO: uses this->_events
}

void LobbySystem::handleLobbyJoin(std::shared_ptr<Engine::Entity> &lobby)
{
    auto &tcp = this->_server->getTcpSocket();
    auto click = lobby->getComponent<Engine::ClickableComponent>();

    if (click->isReleased()) {
        // TODO: connect to lobby
    }
}

void LobbySystem::update()
{
    this->updateFromServer();
    this->handleScroll();
    for (auto &e : this->_entities)
        this->handleLobbyJoin(e);
}