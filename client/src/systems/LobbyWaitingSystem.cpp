//
// Created by paul on 11/14/20.
//

#include "systems/LobbyWaitingSystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TextComponent.hpp"
#include "scenes/SceneType.hpp"

LobbyWaitingSystem::LobbyWaitingSystem(std::shared_ptr<NetworkAccess> &server,
    std::shared_ptr<Engine::AEvents> &events,
    std::shared_ptr<Engine::AScene> &scene) : _server(server), _events(events), _scene(scene)
{
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::TextComponent>();
}

void LobbyWaitingSystem::update()
{
    std::vector<int> data = _server->getTcpSocket()->getDataFromServer();

    if (data.at(0) < 2)
        return;
    if (data.at(0) == 3 && data.at(1) == 45) {
        Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::GAME);
        std::cout << "received client id: " << data.at(2) << std::endl;
        this->_server->setClientId(data.at(2));
        _scene->pushRequest(request);
    }
}

