//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_LOBBYCREATESYSTEM_HPP
#define RTYPE_LOBBYCREATESYSTEM_HPP

#include "components/TextComponent.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class CreateLobbySystem : public Engine::System {
    private:
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;


    public:
    CreateLobbySystem(std::shared_ptr<NetworkAccess> &server,
        std::shared_ptr<Engine::AEvents> &events);
    void increaseNbOClients();
    void decreaseNbOfClients();

    void update() override;
};

#endif //RTYPE_LOBBYCREATESYSTEM_HPP
