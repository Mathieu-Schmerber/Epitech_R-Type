//
// Created by paul on 11/14/20.
//

#ifndef RTYPE_QUITSYSTEMINGAME_HPP
#define RTYPE_QUITSYSTEMINGAME_HPP

#include "graphical/AEvents.hpp"
#include "sceneManagement/AScene.hpp"
#include "ecs/System.hpp"

class QuitSystemInGame : public Engine::System
{
    private:
    std::shared_ptr<Engine::AEvents> _events;
    std::shared_ptr<Engine::AScene> _scene;
    public:
    QuitSystemInGame(
        std::shared_ptr<Engine::AEvents> &events,
        std::shared_ptr<Engine::AScene> &scene);

    void update() override;


};

#endif //RTYPE_QUITSYSTEMINGAME_HPP
