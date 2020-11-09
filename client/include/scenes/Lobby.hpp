//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_LOBBY_HPP
#define RTYPE_LOBBY_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/LobbyCard.hpp"

class Lobby : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;
    std::vector<std::shared_ptr<LobbyCard>> _lobbiesEngines;

    void initEntities() final;
    void initSystems() final;

    public:
    Lobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);

    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void enterLobby(std::shared_ptr<Engine::AScene> &);
void goToInGameScene(std::shared_ptr<Engine::AScene> &);
void goToMenuScene(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_LOBBY_HPP