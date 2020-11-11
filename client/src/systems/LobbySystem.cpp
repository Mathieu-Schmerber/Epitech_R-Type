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
    auto data = tcp->getDataFromServer();
    int size = data.at(0);

    if (size < 6)
        return;
    if (data.at(1) == 0) {
        for (auto &e : this->_entities) {
            if (e->getComponent<LobbyComponent>()->getLobbyId() == data.at(2)) {
                if (data.at(3) == 0)
                    SocketParser::updateLobbyFromTcp(e, data);
                //else
                    //remove element e
                return;
            }
        }
    } else {
        auto entity = SocketParser::unparseTcpLobby(data);
        if (entity)
            this->_scene->spawnEntity(entity); // TODO: pass actual "data" got from server tcp
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
    auto &tcp = this->_server->getTcpSocket();
    auto click = lobby->getComponent<Engine::ClickableComponent>();

    if (click->isReleased()) {
        // TODO: connect to lobby
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
