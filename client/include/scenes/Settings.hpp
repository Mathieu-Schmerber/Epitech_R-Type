//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_SETTINGS_HPP
#define RTYPE_SETTINGS_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/Button.hpp"
#include "SceneEnum.hpp"
#include "entities/Drawable.hpp"
#include <sfml/SpriteSfml.hpp>

enum SettingsSelectorSprite {
    FULLSCREEN_ENABLED,
    FRAMERATE,
    VSYNC_ENABLED,
    MUSIC_ENABLED,
    SOUND_EFFECTS_ENABLED,

};

class Settings : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::vector<std::pair<std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>>, std::shared_ptr<Engine::Drawable>>> _selectorButtonsAndText;

    void initEntities() final;
    void initSystems() final;
    void createSelector(Engine::Point<int> leftPosition, const std::pair<void (*)(std::shared_ptr<Engine::AScene> &), void (*)(std::shared_ptr<Engine::AScene> &)> &callback, const std::string &path, std::unique_ptr<SpriteSFML> text);
public:

    Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
    std::vector<std::pair<std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>>, std::shared_ptr<Engine::Drawable>>> getSelectorButtonsAndText() const;


};

void goToMenuScene(std::shared_ptr<Engine::AScene> &);
void changeWindowEnableFullscreen(std::shared_ptr<Engine::AScene> &);
void changeWindowFrameratePrev(std::shared_ptr<Engine::AScene> &);
void changeWindowFramerateNext(std::shared_ptr<Engine::AScene> &);
void changeWindowVsync(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_SETTINGS_HPP