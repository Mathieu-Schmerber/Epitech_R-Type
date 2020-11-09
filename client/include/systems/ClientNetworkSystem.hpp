//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_CLIENTNETWORKSYSTEM_HPP
#define RTYPE_CLIENTNETWORKSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"
#include "SocketParser.hpp"

class ClientNetworkSystem : public Engine::System
{
private:
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;
    std::unique_ptr<SocketParser> _parser;

    void sendRawInputs();
    void receiveGameData();

public:
    ClientNetworkSystem(std::shared_ptr<NetworkAccess> &server,
                        std::shared_ptr<Engine::AEvents> &events,
                        std::shared_ptr<Engine::AScene> &scene);

    void update() override;


};


#endif //RTYPE_CLIENTNETWORKSYSTEM_HPP
