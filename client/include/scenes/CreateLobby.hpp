//
// Created by Paul on 11/10/20.
//

#ifndef RTYPE_CREATELOBBY_HPP
#define RTYPE_CREATELOBBY_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "NetworkAccess.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

class CreateLobby : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<NetworkAccess> _server;

    void initEntities() final;
    void initSystems() final;

    public:
    CreateLobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server);

    std::shared_ptr<Engine::AWindow> getWindow() const;
};

#endif //RTYPE_CREATELOBBY_HPP
