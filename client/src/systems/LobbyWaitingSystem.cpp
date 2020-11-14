//
// Created by paul on 11/14/20.
//

#include "systems/LobbyWaitingSystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"

LobbyWaitingSystem::LobbyWaitingSystem(std::shared_ptr<NetworkAccess> &server,
    std::shared_ptr<Engine::AEvents> &events,
    std::shared_ptr<Engine::AScene> &scene) : _server(server), _events(events), _scene(scene)
{
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::TextComponent>();
}

void LobbyWaitingSystem::update()
{
    std::cout << "here emilien\n" << std::endl;
}

