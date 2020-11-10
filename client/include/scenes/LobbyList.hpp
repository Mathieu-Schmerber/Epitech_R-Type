//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_LOBBYLIST_HPP
#define RTYPE_LOBBYLIST_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/LobbyCard.hpp"
#include "systems/LobbySystem.hpp"

class LobbyList : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

    public:
    LobbyList(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);
    const std::unique_ptr<Engine::System> &getLobbySystem() const;

    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void scrollDownLobby(std::shared_ptr<Engine::AScene> &);
void scrollUpLobby(std::shared_ptr<Engine::AScene> &);
void goToCreateLobbyScene(std::shared_ptr<Engine::AScene> &);
void goToInGameScene(std::shared_ptr<Engine::AScene> &);
void goToMenuScene(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_LOBBYLIST_HPP