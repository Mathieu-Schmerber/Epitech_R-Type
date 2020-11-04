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

class Settings : public Engine::AScene
{
private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::vector<std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>>> _selectorButtons;

    void initEntities() final;
    void initSystems() final;
    void createSelector(Engine::Point<int> position, void (*onClick)(std::shared_ptr<Engine::AScene> &callback));
    void setFrameRate(int newFramerate);
    int _frameRate = 30;
public:

    Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);

    std::shared_ptr<Engine::AWindow> getWindow() const;

};

void goToMenuScene(std::shared_ptr<Engine::AScene> &);
void changeWindowEnableFullscreen(std::shared_ptr<Engine::AScene> &);
void changeWindowFramerate(std::shared_ptr<Engine::AScene> &);
void changeWindowVsync(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &);
void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_SETTINGS_HPP