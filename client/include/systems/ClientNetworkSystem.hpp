//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_CLIENTNETWORKSYSTEM_HPP
#define RTYPE_CLIENTNETWORKSYSTEM_HPP

#include "networking/AServer.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class ClientNetworkSystem : Engine::System
{
private:
    std::shared_ptr<Engine::AServer> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;
    short _clientId;

    void sendRawInputs();
    void updateGameData();

public:
    ClientNetworkSystem(std::shared_ptr<Engine::AServer> &server,
                        std::shared_ptr<Engine::AEvents> &events,
                        std::shared_ptr<Engine::AScene> &scene);

    void setClientId(short clientId);

    void update() override;


};


#endif //RTYPE_CLIENTNETWORKSYSTEM_HPP
