//
// Created by paul on 11/14/20.
//

#include "components/TransformComponent.hpp"
#include "entities/PlayerAndStarshipEntity.hpp"
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
    Engine::Point<double> pos{532, -100};
    int nbOfPlayer = 0;
    std::vector<int> data = _server->getTcpSocket()->getDataFromServer();

    if (data.at(0) < 2)
        return;
    if (data.at(0) == 3 && data.at(1) == 45) {
        Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::GAME);
        this->_server->setClientId(data.at(2));
        _scene->pushRequest(request);
    }
    if (data.at(0) == 4 && data.at(1) == 49) {
        //New user to lobby
        int idNewPlayer = data.at(2);
        int idClientMaster = data.at(3);
        for (auto &e : this->_entities) {
            if (e->getComponent<PlayerAndStarshipComponent>()) {
                pos = e->getComponent<Engine::TransformComponent>()->getPos();
                nbOfPlayer++;
            }
        }

        std::shared_ptr<Engine::Entity> playerAndStarShipCard = std::make_shared<PlayerAndStarshipEntity>("Player " + std::to_string(nbOfPlayer + 1), idNewPlayer);
        playerAndStarShipCard->getComponent<Engine::TransformComponent>()->setPos({pos.x, pos.y + 200});
        this->_scene->spawnEntity(playerAndStarShipCard);
    }
    if (data.at(0) == 4 && data.at(1) == 50) {
        //User quit the lobby
        int idQuitPlayer = data.at(2);
        int idClientMaster = data.at(3);
        for (auto &e : this->_entities) {
            if (e->getComponent<PlayerAndStarshipComponent>()) {
                auto id = e->getComponent<PlayerAndStarshipComponent>()->getId();
                if (id == idQuitPlayer) {
                    this->_scene->despawnEntity(e);
                    return;
                }
            }
        }

    }
}

