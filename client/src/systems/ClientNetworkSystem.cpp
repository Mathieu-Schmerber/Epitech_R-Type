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
    this->_parser = std::make_unique<SocketParser>();
    this->_lastData = std::vector<int>(UDP_BUFFER_SIZE);
}

void ClientNetworkSystem::sendRawInputs()
{
    auto &socket = this->_server->getUdpSocket();
    auto query = SocketParser::parseUdpInputs(this->_server->getClientId(), this->_events->getKeysPressed(), this->_events->getKeysReleased());

    socket->sendDataToServer(query);
}

std::vector<std::vector<int>> splitVector(std::vector<int> mainVec, int partSize)
{
    std::vector<std::vector<int>> subVecs{};

    auto itr = mainVec.begin();
    size_t fullSize = mainVec.size();

    for (int i = 0; fullSize > partSize; ++i) {
        fullSize -= partSize;
        subVecs.emplace_back(std::vector<int>{itr, itr + partSize});
        itr += partSize;
    }
    return subVecs;
}

void ClientNetworkSystem::receiveGameData()
{
    auto entitiesCopy = this->_entities;
    auto &socket = this->_server->getUdpSocket();
    auto data = socket->getDataFromServer();
    std::vector<std::vector<int>> packets = splitVector(data, UDP_ENTITY_SIZE);

    this->_parser->refreshTimer((data != this->_lastData));
    this->_lastData = data;

    std::vector<int> ids;
    for (auto &p : packets) {
        ids.push_back(p.at(1));
    }

    for (auto &e : entitiesCopy) {
        if (!Engine::Utils::isInVector(ids, e->getComponent<Engine::NetworkComponent>()->getNetworkId())) {
            _scene->despawnEntity(e);
        }
    }

    entitiesCopy = _entities;


    for (auto &p : packets) {
        if (p.at(0) == -1)
            break;
        std::function<bool(std::shared_ptr<Engine::Entity>)> x3 = [p](std::shared_ptr<Engine::Entity> entity){
            return p.at(1) == entity->getComponent<Engine::NetworkComponent>()->getNetworkId();
        };
        if (Engine::Utils::isInVector(entitiesCopy, x3))
            _parser->updateEntityFromUdp(Engine::Utils::getInVector(entitiesCopy, x3), p);
        else {
            auto toSpawn = this->_parser->unparseUdpEntity(p);
            if (toSpawn)
                this->_scene->spawnEntity(toSpawn);
        }
    }



    //for (auto &e : copy) {
    //    for (auto &p : packets) {
    //        Engine::Utils::isInVector(packets, x3);
//
    //    }
    //    dataSection = std::vector<int>(data.begin() + increment, data.begin() + increment + UDP_ENTITY_SIZE);
    //    std::cout << e->getComponent<Engine::NetworkComponent>()->getNetworkId() << " " << dataSection.at(1) << std::endl;
    //    if (!dataSection.empty() && dataSection.at(1) == e->getComponent<Engine::NetworkComponent>()->getNetworkId()) {
    //        this->_parser->updateEntityFromUdp(e, dataSection);
    //    } else if (!dataSection.empty())
    //        this->_scene->despawnEntity(e);
    //}
    //for (int i = 0; i < rest; ++i) {
    //    dataSection = std::vector<int>(data.begin() + increment, data.begin() + increment + UDP_ENTITY_SIZE);
    //    if (dataSection.at(0) == -1)
    //        return;
    //    auto toSpawn = this->_parser->unparseUdpEntity(dataSection);
    //    if (toSpawn)
    //        this->_scene->spawnEntity(toSpawn);
    //}
}



void ClientNetworkSystem::update()
{
    if (this->_server->getClientId() != -1) {
        this->sendRawInputs();
        this->receiveGameData();
    }
}