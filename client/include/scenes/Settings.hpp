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
#define SETTINGS_BACKGROUND_POSITION_X 0
#define SETTINGS_BACKGROUND_POSITION_Y 0

#define FULLSCREEN_TEXT_PATH "../../client/assets/texts/fullscreen_text_462x51.png"
#define FULLSCREEN_TEXT_POSITION_X 498
#define FULLSCREEN_TEXT_POSITION_Y 250

#define FRAMERATE_TEXT_PATH "../../client/assets/texts/framerate_text_415x51.png"
#define FRAMERATE_TEXT_POSITION_X 545
#define FRAMERATE_TEXT_POSITION_Y 400

#define VSYNC_TEXT_PATH "../../client/assets/texts/vsync_text_228x51.png"
#define VSYNC_TEXT_POSITION_X 732
#define VSYNC_TEXT_POSITION_Y 550

#define MUSIC_TEXT_PATH "../../client/assets/texts/music_text_228x51.png"
#define MUSIC_TEXT_POSITION_X 732
#define MUSIC_TEXT_POSITION_Y 700

#define SOUND_EFFECTS_TEXT_PATH "../../client/assets/texts/sound_effects_text_573x51.png"
#define SOUND_EFFECTS_TEXT_POSITION_X 387
#define SOUND_EFFECTS_TEXT_POSITION_Y 850


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