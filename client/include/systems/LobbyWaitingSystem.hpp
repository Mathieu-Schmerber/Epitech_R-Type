//
// Created by paul on 11/14/20.
//

#ifndef RTYPE_LOBBYWAITINGSYSTEM_HPP
#define RTYPE_LOBBYWAITINGSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class LobbyWaitingSystem : public Engine::System {
    private:
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;

    public:
    LobbyWaitingSystem(std::shared_ptr<NetworkAccess> &server,
        std::shared_ptr<Engine::AEvents> &events,
        std::shared_ptr<Engine::AScene> &scene);

    void update() override;
};

#endif //RTYPE_LOBBYWAITINGSYSTEM_HPP
