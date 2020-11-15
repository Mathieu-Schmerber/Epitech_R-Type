//
// Created by mathi on 09/11/2020.
//

#include "SocketParser.hpp"
#include "components/LobbyComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "systems/LobbySystem.hpp"
#include "entities/LobbyCard.hpp"
#include "enumerations/Inputs.hpp"
#include "scenes/SceneType.hpp"

LobbySystem::LobbySystem(std::shared_ptr<NetworkAccess> &server, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<Engine::AScene> &scene)
: _server(server), _events(events), _scene(scene), Engine::System()
{
    this->addDependency<LobbyComponent>();
    this->addDependency<Engine::ClickableComponent>();
    this->addDependency<Engine::TransformComponent>();
}

void LobbySystem::updateFromServer()
{
    auto &tcp = this->_server->getTcpSocket();
    auto data = tcp->getDataFromServer();
    int size = data.at(0);

    if (size < 2)
        return;
    if (data.at(1) == 0) {
        for (auto &e : this->_entities) {
            if (e->getComponent<LobbyComponent>()->getLobbyId() == data.at(2)) {
                if (data.at(3) == 0) {
                    SocketParser::updateLobbyFromTcp(e, data);
                }
                return;
            }
        }
    } else if (data.at(0) == 3 && data.at(1) == 46) {
        for (auto e : this->_entities) {
            auto lobbyComp = e->getComponent<LobbyComponent>();
            if (lobbyComp && lobbyComp->getLobbyId() == data.at(2)) {
                _scene->despawnEntity(e);
                return;
            }
        }
    } else {
        double lastLobbyCardPositionY = -190;
        for (auto &e : this->_entities) {
            if (e->getComponent<LobbyComponent>()) {
               lastLobbyCardPositionY = e->getComponent<Engine::TransformComponent>()->getPos().y;
            }
        }
        auto entity = SocketParser::unparseTcpLobby(data);

        if (entity) {
            entity->getComponent<Engine::TransformComponent>()->setPos({535, lastLobbyCardPositionY + 250});
            this->_scene->spawnEntity(entity); // TODO: pass actual "data" got from server tcp
        }
    }
}

void LobbySystem::handleScroll()
{
    auto wheel = this->_events->getScrollState();
    auto arrow = this->_events->getKeysReleased();

    if ((wheel.direction == wheel.vertical && wheel.movement < 0) ||
    (!this->_events->getKeysReleased().empty() && arrow.front() == Engine::Inputs::Down)) {
       scrollDownLobbies();
    } else if ((wheel.direction == wheel.vertical && wheel.movement > 0)||
        (!this->_events->getKeysReleased().empty() && arrow.front() == Engine::Inputs::Up)) {
        scrollUpLobbies();
    }
}

void LobbySystem::handleLobbyJoin(std::shared_ptr<Engine::Entity> &lobby)
{
    bool waitingForAnswer = true;
    auto &tcp = this->_server->getTcpSocket();
    auto click = lobby->getComponent<Engine::ClickableComponent>();
    unsigned short info = lobby->getComponent<LobbyComponent>()->getLobbyId(); //Et autres getter à la place de getLobbyId
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::LOBBY_WAITING);

    if (click->isReleased()) {
        // TODO: connect to lobby, faire la connexion au lobby TCP ici
        std::cout << "Pouet pouet fait le dindon" << std::endl;
        std::vector<int> toSend;
        toSend.push_back(3);
        toSend.push_back(0);
        toSend.push_back(info);
        tcp->sendToServer(toSend);
        while (waitingForAnswer) {
            std::vector<int> data = tcp->getDataFromServer();
            if (data.at(0) != 3 || data.at(1) != 42)
                continue;
            _server->openSockets(data.at(2));
            waitingForAnswer = false;
        }
        toSend.clear();
        toSend.push_back(3);
        toSend.push_back(43);
        toSend.push_back(_server->getPortServer());
        tcp->sendToServer(toSend);
        this->_scene->pushRequest(request);
    }
}

void LobbySystem::update()
{
    this->handleScroll();
    for (auto &e : this->_entities)
        this->handleLobbyJoin(e);
    this->updateFromServer();
}

void LobbySystem::scrollUpLobbies()
{
    auto firstCardPosition = _entities.front()->getComponent<Engine::TransformComponent>()->getPos();
    for (auto &e: this->_entities) {
        auto tcomponent = e->getComponent<Engine::TransformComponent>();
        auto pos = tcomponent->getPos();
        if (firstCardPosition.y < 60)
            tcomponent->setPos(Engine::Point<double>{pos.x, pos.y + 50});
    }
}

void LobbySystem::scrollDownLobbies()
{
    auto lastCardPosition = _entities.back()->getComponent<Engine::TransformComponent>()->getPos();
    for (auto &e: this->_entities) {
        auto tcomponent = e->getComponent<Engine::TransformComponent>();
        auto pos = tcomponent->getPos();
        if (lastCardPosition.y > 810)
            tcomponent->setPos(Engine::Point<double>{pos.x, pos.y - 50});
    }
}
