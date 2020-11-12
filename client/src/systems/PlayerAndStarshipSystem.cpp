//
// Created by paul on 11/10/20.
//


#include "SocketParser.hpp"
#include "components/ClickableComponent.hpp"
#include "systems/PlayerAndStarshipSystem.hpp"
#include "entities/LobbyCard.hpp"
#include "components/TextComponent.hpp"

PlayerAndStarshipSystem::PlayerAndStarshipSystem(std::shared_ptr<NetworkAccess> &server, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<Engine::AScene> &scene)
    : _server(server), _events(events), _scene(scene), Engine::System()
{
    this->addDependency<Engine::ClickableComponent>();
    this->addDependency<Engine::TransformComponent>();
}

void PlayerAndStarshipSystem::updateFromServer()
{

}

void PlayerAndStarshipSystem::handleLobbyJoin(std::shared_ptr<Engine::Entity> &playerAndStarship)
{

}

void PlayerAndStarshipSystem::update()
{

}
