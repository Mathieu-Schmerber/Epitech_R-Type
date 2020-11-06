//
// Created by mathi on 06/11/2020.
//

#include "ServerNetworkSystem.hpp"
#include "SocketParser.hpp"
#include "components/NetworkComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/SpriteComponent.hpp"

ServerNetworkSystem::ServerNetworkSystem(std::vector<Client> &players, std::unique_ptr<UdpSocketInput> &reception)
: _players(players), _reception(reception), Engine::System()
{
    this->addDependency<Engine::NetworkComponent>();
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->addDependency<Engine::ControllerComponent>();
}

void ServerNetworkSystem::receiveClientInputs()
{
    //std::vector<int> data = this->_reception.get()->getDataFromServer();
    //TODO: Comment because crash
    /*auto inputs = SocketParser::unparseUdpInputs(data);
    std::shared_ptr<Engine::Entity> affected;

    if (!data.empty()) {
        affected = this->_entities.at(data.at(0));
        affected->getComponent<Engine::ControllerComponent>()->setPressed(inputs.first);
        affected->getComponent<Engine::ControllerComponent>()->setReleased(inputs.second);
    }*/
}

void ServerNetworkSystem::sendGameData()
{
    for (auto &e : this->_entities) {
        //TODO: for (auto &cli : this->_players)
        //TODO: cli->getUdpSocket()->send(SocketParser::parseEntityUdp(e))
    }
}

void ServerNetworkSystem::update()
{
    if (this->_reception.get())
        this->receiveClientInputs();
    this->sendGameData();
}