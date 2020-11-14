//
// Created by mathi on 06/11/2020.
//

#include <components/ButtonComponent.hpp>
#include "systems/ClientNetworkSystem.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "SocketParser.hpp"

ClientNetworkSystem::ClientNetworkSystem(std::shared_ptr<NetworkAccess> &server, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<Engine::AScene> &scene)
: _server(server), _events(events), _scene(scene)
{
    this->addDependency<Engine::NetworkComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->_parser = std::make_unique<SocketParser>();
    this->_lastData = std::vector<int>(UDP_BUFFER_SIZE);
}

void ClientNetworkSystem::sendRawInputs()
{
    auto &socket = this->_server->getUdpSocket();
    auto query = SocketParser::parseUdpInputs(this->_server->getClientId(), this->_events->getKeysPressed(), this->_events->getKeysReleased());

    socket->sendDataToServer(query);
}

void ClientNetworkSystem::receiveGameData()
{
    auto copy = this->_entities;
    auto &socket = this->_server->getUdpSocket();
    auto data = socket->getDataFromServer();
    int increment = 0;
    int rest;
    std::vector<int> dataSection;

    this->_parser->refreshTimer((data != this->_lastData));
    this->_lastData = data;
    for (auto &e : copy) {
        if (increment >= UDP_BUFFER_SIZE)
            return;
        dataSection = std::vector<int>(data.begin() + increment, data.begin() + increment + UDP_ENTITY_SIZE);
        if (!dataSection.empty() && dataSection.at(1) == e->getComponent<Engine::NetworkComponent>()->getNetworkId()) {
            this->_parser->updateEntityFromUdp(e, dataSection);
            increment += UDP_ENTITY_SIZE;
        } else if (!dataSection.empty())
            this->_scene->despawnEntity(e);
    }
    rest = (UDP_BUFFER_SIZE - increment) / UDP_ENTITY_SIZE;
    for (int i = 0; i < rest; ++i) {
        dataSection = std::vector<int>(data.begin() + increment, data.begin() + increment + UDP_ENTITY_SIZE);
        if (dataSection.at(0) == -1)
            return;
        auto toSpawn = this->_parser->unparseUdpEntity(dataSection);
        if (toSpawn)
            this->_scene->spawnEntity(toSpawn);
        increment += UDP_ENTITY_SIZE;
    }
}



void ClientNetworkSystem::update()
{
    if (this->_server->getClientId() != -1) {
        this->sendRawInputs();
        this->receiveGameData();
    }
}