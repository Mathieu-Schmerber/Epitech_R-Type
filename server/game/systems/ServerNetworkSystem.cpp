//
// Created by mathi on 06/11/2020.
//

#include "components/TextComponent.hpp"
#include "tools/Utils.hpp"
#include "ServerNetworkSystem.hpp"
#include "SocketParser.hpp"
#include "components/NetworkComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/SpriteComponent.hpp"

ServerNetworkSystem::ServerNetworkSystem(std::vector<std::shared_ptr<Client>> &players, std::unique_ptr<UdpSocketInput> &reception)
: _players(players), _reception(reception), Engine::System()
{
    this->addDependency<Engine::NetworkComponent>();
    this->addDependency<Engine::TransformComponent>();
}

void ServerNetworkSystem::receiveClientInputs()
{
    std::vector<int> data = this->_reception.get()->getDataFromServer();
    auto inputs = SocketParser::unparseUdpInputs(data);
    std::shared_ptr<Engine::Entity> affected;
    Engine::ControllerComponent *controller = nullptr;

    if (!data.empty() && data.at(0) != -1 && !this->_entities.empty() && this->_entities.size() > data.at(0)) {
        affected = this->_entities.at(data.at(0));
        controller = affected->getComponent<Engine::ControllerComponent>();
        if (controller) {
            affected->getComponent<Engine::ControllerComponent>()->setPressed(inputs.first);
            affected->getComponent<Engine::ControllerComponent>()->setReleased(inputs.second);
        }
    }
}

void ServerNetworkSystem::sendGameData()
{
    std::vector<int> data;

    for (auto &e : this->_entities) {
        if (e->getComponent<Engine::SpriteComponent>() || e->getComponent<Engine::TextComponent>()) {
            auto section = SocketParser::parseUdpEntity(e);
            data.insert(data.end(), section.begin(), section.end());
        }
    }
    data.resize(UDP_BUFFER_SIZE, -1);
    for (auto &cli : this->_players)
        cli->sendToClient(data);
}

void ServerNetworkSystem::update()
{
    if (this->_reception.get())
        this->receiveClientInputs();
    this->sendGameData();
}