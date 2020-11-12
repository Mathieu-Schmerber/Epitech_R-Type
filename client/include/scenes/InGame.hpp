//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_INGAME_HPP
#define RTYPE_INGAME_HPP

#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "NetworkAccess.hpp"

class InGame : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

public:
    InGame(std::shared_ptr<Engine::AWindow> &window,
           std::shared_ptr<Engine::AEvents> &events,
           std::shared_ptr<NetworkAccess> &server);
    ~InGame() = default;

    void onFocus() override;
    void onExit() override;

};


#endif //RTYPE_INGAME_HPP
