//
// Created by mathi on 09/11/2020.
//

#include "SocketParser.hpp"
#include "components/LobbyComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "systems/LobbySystem.hpp"
#include "entities/LobbyCard.hpp"
#include "enumerations/Inputs.hpp"

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
    //TODO: auto data = tcp->getDataFromServer();
    unsigned short lobbyId = 0; // TODO: get id from the tcp data at a certain index

    for (auto &e : this->_entities) {
        if (e->getComponent<LobbyComponent>()->getLobbyId() == lobbyId) {
            SocketParser::updateLobbyFromTcp(e, {});
            return;
        }
    }
    auto entity = SocketParser::unparseTcpLobby({});
    if (entity)
        this->_scene->spawnEntity(entity); // TODO: pass actual "data" got from server tcp
}

void LobbySystem::handleScroll()
{
    auto wheel = this->_events->getScrollState();

    if (wheel.direction == wheel.vertical && wheel.movement < 0) {
       scrollDownLobbies();
    } else if (wheel.direction == wheel.vertical && wheel.movement > 0) {
        scrollUpLobbies();
    }
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

void LobbySystem::scrollUpLobbies()
{
    auto firstCardPosition = _entities.front()->getComponent<Engine::TransformComponent>()->getPos();
    for (auto &e: this->_entities) {
        auto tcomponent = e->getComponent<Engine::TransformComponent>();
        auto pos = tcomponent->getPos();
        if (firstCardPosition.y < 60)
            tcomponent->setPos(Engine::Point<int>{pos.x, pos.y + 50});
    }
}

void LobbySystem::scrollDownLobbies()
{
    auto lastCardPosition = _entities.back()->getComponent<Engine::TransformComponent>()->getPos();
    for (auto &e: this->_entities) {
        auto tcomponent = e->getComponent<Engine::TransformComponent>();
        auto pos = tcomponent->getPos();
        if (lastCardPosition.y > 810)
            tcomponent->setPos(Engine::Point<int>{pos.x, pos.y - 50});
    }
}
