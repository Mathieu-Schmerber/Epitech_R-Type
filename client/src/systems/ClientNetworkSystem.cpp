//
// Created by mathi on 06/11/2020.
//

#include "systems/ClientNetworkSystem.hpp"
#include "components/NetworkComponent.hpp"
#include "SocketParser.hpp"

ClientNetworkSystem::ClientNetworkSystem(std::shared_ptr<Engine::AServer> &server, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<Engine::AScene> &scene)
: _server(server), _events(events), _scene(scene), _clientId(-1)
{
    this->addDependency<Engine::NetworkComponent>();
}

void ClientNetworkSystem::sendRawInputs()
{
    auto &socket = this->_server->getUdpSocket();
    auto query = SocketParser::parseUdpInputs(this->_clientId, this->_events->getKeysPressed(), this->_events->getKeysReleased());

    socket->sendDataToServer(query);
}

void ClientNetworkSystem::updateGameData()
{
    auto &socket = this->_server->getUdpSocket();
    auto entry = socket->getDataFromServer();

    for (auto &e : this->_entities) {
        if (!entry.empty() && entry.at(0) == e->getComponent<Engine::NetworkComponent>()->getNetworkId()) {
            SocketParser::updateEntityFromUdp(e, entry);
            return;
        }
    }
    this->_scene->spawnEntity(SocketParser::unparseUdpEntity(entry));
}

void ClientNetworkSystem::update()
{
    if (this->_clientId != -1) {
        this->sendRawInputs();
        this->updateGameData();
    }
}

void ClientNetworkSystem::setClientId(short clientId)
{
    _clientId = clientId;
}
