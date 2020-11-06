//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_SERVERNETWORKSYSTEM_HPP
#define RTYPE_SERVERNETWORKSYSTEM_HPP

#include "ecs/System.hpp"

class ServerNetworkSystem : Engine::System {
private:
public:
    ServerNetworkSystem();

    void update() override;
};


#endif //RTYPE_SERVERNETWORKSYSTEM_HPP
