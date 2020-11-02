//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_MAINMENU_HPP
#define RTYPE_MAINMENU_HPP

#include "SceneType.hpp"
#include "AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

#define RTYPE_LOGO_PATH "../../client/assets/images/others/r_type_logo_700x204.png"
#define START_BUTTON_PATH "../../client/assets/images/buttons/start/start_button_full_684x57.png"
#define SETTINGS_BUTTON_PATH "../../client/assets/images/buttons/settings/settings_button_full_1104x57.png"
#define HOW_TO_PLAY_BUTTON_PATH "../../client/assets/images/buttons/how_to_play/how_to_play_button_full_1344x57.png"
#define QUIT_BUTTON_PATH "../../client/assets/images/buttons/quit/quit_button_full_558x57.png"
#define MENU_PARALLAX_PATH "../../client/assets/images/parallax/parallax_3_3840x1080.png"

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