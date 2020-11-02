//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_SETTINGS_HPP
#define RTYPE_SETTINGS_HPP

#include "SceneType.hpp"
#include "AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

#define SETTINGS_BACKGROUND_PATH "../../client/assets/images/background/background_2.png"
#define SETTINGS_BACKGROUND_WIDTH 1920
#define SETTINGS_BACKGROUND_HEIGHT 1080
#define SETTINGS_BACKGROUND_POSITION_X 0
#define SETTINGS_BACKGROUND_POSITION_Y 0

class Settings : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;

    void initEntities() final;
    void initSystems() final;

public:

    Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
};

void testCallback(std::shared_ptr<Settings> menu);

#endif //RTYPE_SETTINGS_HPP