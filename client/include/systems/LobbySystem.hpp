//
// Created by mathi on 09/11/2020.
//

#ifndef RTYPE_LOBBYSYSTEM_HPP
#define RTYPE_LOBBYSYSTEM_HPP

#include "NetworkAccess.hpp"
#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class LobbySystem : public Engine::System {
    private:
        std::shared_ptr<NetworkAccess> _server;
        std::shared_ptr<Engine::AEvents> _events;
        std::shared_ptr<Engine::AScene> _scene;

        void updateFromServer();
        void handleScroll();
        void handleLobbyJoin(std::shared_ptr<Engine::Entity> &lobby);

    public:
        LobbySystem(std::shared_ptr<NetworkAccess> &server,
                    std::shared_ptr<Engine::AEvents> &events,
                    std::shared_ptr<Engine::AScene> &scene);
        void scrollDownLobbies();
        void scrollUpLobbies();

    void update() override;
};


#endif //RTYPE_LOBBYSYSTEM_HPP
