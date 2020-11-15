//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_SERVERNETWORKSYSTEM_HPP
#define RTYPE_SERVERNETWORKSYSTEM_HPP

#include "ecs/System.hpp"
#include "Client.hpp"
#include "networking/UDP/UdpSocketInput.hpp"

class ServerNetworkSystem : public Engine::System {
private:
    std::vector<std::shared_ptr<Client>> _players;
    std::reference_wrapper<std::unique_ptr<UdpSocketInput>> _reception;

    void receiveClientInputs();
    void sendGameData();

public:
    ServerNetworkSystem(std::vector<std::shared_ptr<Client>> &players, std::unique_ptr<UdpSocketInput> &reception);

    void update() override;
};

#endif //RTYPE_SERVERNETWORKSYSTEM_HPP
