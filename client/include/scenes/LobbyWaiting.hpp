//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_LOBBYWAITING_HPP
#define RTYPE_LOBBYWAITING_HPP

#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

class LobbyWaiting : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

    public:
    LobbyWaiting(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);

    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void goBackToCreateLobby(std::shared_ptr<Engine::AScene> &);
void goToInGamesScene(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_LOBBYWAITING_HPP
