//
// Created by paul on 11/10/20.
//

#include "SocketParser.hpp"
#include "components/TransformComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/CreateLobbyComponent.hpp"
#include "systems/LobbyCreateSystem.hpp"
#include "entities/LobbyCard.hpp"
#include "enumerations/Inputs.hpp"

CreateLobbySystem::CreateLobbySystem(std::shared_ptr<NetworkAccess> &server, std::shared_ptr<Engine::AEvents> &events)
    : _server(server), _events(events), Engine::System()
{
    this->addDependency<Engine::ClickableComponent>();
    this->addDependency<Engine::TransformComponent>();
}

void CreateLobbySystem::update()
{
    auto input = this->_events->getKeysReleased();
    auto lobbyComponent = _entities.front()->getComponent<CreateLobbyComponent>();

    if (!input.empty()) {
        if (input.front() == Engine::Inputs::Up) {
            increaseNbOClients();
        } else if (input.front() == Engine::Inputs::Down) {
            decreaseNbOfClients();
        }
    }

    for (auto &e : this->_entities) {
        auto text = e->getComponent<Engine::TextComponent>();
        if (text) {
            text->getText()->setString("Number of players : " + std::to_string(lobbyComponent->getNbMaxClients()));
        }
    }
}

void CreateLobbySystem::increaseNbOClients()
{
    auto lobbyComponent = _entities.front()->getComponent<CreateLobbyComponent>();

    if (lobbyComponent->getNbMaxClients() < 9) {
        lobbyComponent->setNbMaxClient(lobbyComponent->getNbMaxClients() + 1);
    }
}

void CreateLobbySystem::decreaseNbOfClients()
{
    auto lobbyComponent = _entities.front()->getComponent<CreateLobbyComponent>();

    if (lobbyComponent->getNbMaxClients() > 1) {
        lobbyComponent->setNbMaxClient(lobbyComponent->getNbMaxClients() - 1);
    }
}

