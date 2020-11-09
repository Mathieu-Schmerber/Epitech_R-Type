//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_HOW_TO_PLAY_HPP
#define RTYPE_HOW_TO_PLAY_HPP

#include "SceneType.hpp"
#include "sceneManagement/AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"
#include "entities/Drawable.hpp"
#include "SceneEnum.hpp"

enum HowToPlayContext {
    PRELUDE,
    WEAPONS,
    HEALTH,
    BONUS
};

class HowToPlay : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::vector<std::shared_ptr<Engine::Entity>> _enginesDrawableHowToPlayScreen;
    int _enginesDrawableHowToPlayScreenIndex = 0;
    std::vector<std::shared_ptr<Engine::Entity>> _enginesDrawableHowToPlayBonus;
    std::shared_ptr<Engine::Entity> _enginesPowerUp;

    void initEntities() final;
    void initSystems() final;
    void onFocus() final;

    public:
    std::vector<std::shared_ptr<Engine::Entity>> getEnginesDrawable() const;
    int getEnginesDrawableIndex() const;
    void setEnginesDrawableIndex(unsigned char index);
    std::vector<std::shared_ptr<Engine::Entity>> getEnginesDrawableBonus() const;
    std::shared_ptr<Engine::Entity> getPowerUpEngine() const;
    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &);
void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &m);

#endif //RTYPE_HOW_TO_PLAY_HPP//
