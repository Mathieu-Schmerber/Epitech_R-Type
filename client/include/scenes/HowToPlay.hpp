/*!
 * @file HowToPlay.hpp
 * @brief HowToPlay scene declaration
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

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
    /*!
     * \brief HowToPlay scene constructor
     * \param window window to be stored as reference
     * \param events events manager to be stored as reference
     *
     * Create the "HowToPlay" scene
    */
    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::vector<std::shared_ptr<Engine::Entity>> getEnginesDrawable() const;
    int getEnginesDrawableIndex() const;
    std::vector<std::shared_ptr<Engine::Entity>> getEnginesDrawableBonus() const;
    std::shared_ptr<Engine::Entity> getPowerUpEngine() const;
    std::shared_ptr<Engine::AWindow> getWindow() const;
    void setEnginesDrawableIndex(unsigned char index);
};

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &);
void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &);

#endif //RTYPE_HOW_TO_PLAY_HPP//
