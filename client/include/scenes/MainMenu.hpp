//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_MAINMENU_HPP
#define RTYPE_MAINMENU_HPP

#include "SceneType.hpp"
#include "AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

class MainMenu : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;

    void initEntities() final;
    void initSystems() final;

public:

    MainMenu(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
};

void playCallback(std::shared_ptr<MainMenu> menu);

#endif //RTYPE_MAINMENU_HPP