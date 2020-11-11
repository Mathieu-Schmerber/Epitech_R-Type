//
// Created by mathi on 06/11/2020.
//

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
    this->addDependency<Engine::SpriteComponent>();
}

void ServerNetworkSystem::receiveClientInputs()
{
    std::vector<int> data = this->_reception.get()->getDataFromServer();
    auto inputs = SocketParser::unparseUdpInputs(data);
    std::shared_ptr<Engine::Entity> affected;
    Engine::ControllerComponent *controller = nullptr;

    if (!data.empty() && !this->_entities.empty()) {
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
    for (auto &e : this->_entities) {
        for (auto &cli : this->_players) {
            auto data = SocketParser::parseUdpEntity(e);
            cli->sendToClient(data);
            std::cout << "heho" << std::endl;
        }
    }
}

void ServerNetworkSystem::update()
{
    if (this->_reception.get())
        this->receiveClientInputs();
    this->sendGameData();
}