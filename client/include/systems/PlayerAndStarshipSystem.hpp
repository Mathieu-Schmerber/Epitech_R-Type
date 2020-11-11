//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP
#define RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class PlayerAndStarshipSystem : public Engine::System {
    private:
    std::shared_ptr<NetworkAccess> _server;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;

    void updateFromServer();
    void handleLobbyJoin(std::shared_ptr<Engine::Entity> &);

    public:
    PlayerAndStarshipSystem(std::shared_ptr<NetworkAccess> &server,
        std::shared_ptr<Engine::AEvents> &events,
        std::shared_ptr<Engine::AScene> &scene);

    void update() override;
};

#endif //RTYPE_PLAYERANDSTARSHIPSYSTEM_HPP
