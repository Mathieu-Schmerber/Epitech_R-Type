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
#include "entities/Button.hpp"

#define GO_BACK_BUTTON_PATH "../../client/assets/images/buttons/left_arrow/left_arrow_full_192x64.png"
#define GO_BACK_BUTTON_POSITION_X 30
#define GO_BACK_BUTTON_POSITION_Y 30
#define GO_BACK_BUTTON_Y 0
#define GO_BACK_BUTTON_HEIGHT 64
#define GO_BACK_BUTTON_WIDTH 64
#define GO_BACK_BUTTON_X_IDLE 0
#define GO_BACK_BUTTON_X_HOVER 64
#define GO_BACK_BUTTON_X_CLICKED 128

#define GO_NEXT_BUTTON_PATH "../../client/assets/images/buttons/right_arrow/right_arrow_full_192x64.png"
#define GO_NEXT_BUTTON_POSITION_X 1826
#define GO_NEXT_BUTTON_POSITION_Y 946
#define GO_NEXT_BUTTON_Y 0
#define GO_NEXT_BUTTON_HEIGHT 64
#define GO_NEXT_BUTTON_WIDTH 64
#define GO_NEXT_BUTTON_X_IDLE 0
#define GO_NEXT_BUTTON_X_HOVER 64
#define GO_NEXT_BUTTON_X_CLICKED 128

#define HOW_TO_PLAY_1_PATH "../../client/assets/images/how_to_play/how_to_play_1.png"
#define HOW_TO_PLAY_1_POSITION_X 0
#define HOW_TO_PLAY_1_POSITION_Y 0

#define HOW_TO_PLAY_2_PATH "../../client/assets/images/how_to_play/how_to_play_2.png"
#define HOW_TO_PLAY_2_POSITION_X 0
#define HOW_TO_PLAY_2_POSITION_Y 0

#define HOW_TO_PLAY_3_PATH "../../client/assets/images/how_to_play/how_to_play_3.png"
#define HOW_TO_PLAY_3_POSITION_X 0
#define HOW_TO_PLAY_3_POSITION_Y 0

#define HOW_TO_PLAY_4_PATH "../../client/assets/images/how_to_play/how_to_play_4.png"
#define HOW_TO_PLAY_4_POSITION_X 0
#define HOW_TO_PLAY_4_POSITION_Y 0

#define BONUS_1_PATH "../../client/assets/images/bonus/bonus_1_160x36_40x36.png"
#define BONUS_1_POSITION_X 860
#define BONUS_1_POSITION_Y 460
#define BONUS_1_WIDTH 40
#define BONUS_1_HEIGHT 36

#define BONUS_2_PATH "../../client/assets/images/bonus/bonus_2_160x36_40x36.png"
#define BONUS_2_POSITION_X 960
#define BONUS_2_POSITION_Y 460
#define BONUS_2_WIDTH 40
#define BONUS_2_HEIGHT 36

#define BONUS_3_PATH "../../client/assets/images/bonus/bonus_3_160x36_40x36.png"
#define BONUS_3_POSITION_X 1060
#define BONUS_3_POSITION_Y 460
#define BONUS_3_WIDTH 40
#define BONUS_3_HEIGHT 36

#define BONUS_SCALE_X 1.75
#define BONUS_SCALE_Y 1.75

#define POWER_UP_PATH "../../client/assets/images/weapons/power_up_1_100x20_25x20.png"
#define POWER_UP_POSITION_X 924
#define POWER_UP_POSITION_Y 460
#define POWER_UP_WIDTH 24
#define POWER_UP_HEIGHT 20
#define POWER_UP_SCALE_X 3
#define POWER_UP_SCALE_Y 3

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
    std::vector<std::shared_ptr<Engine::Drawable>> _enginesDrawableHowToPlayScreen;
    int _enginesDrawableHowToPlayScreenIndex = 0;
    std::vector<std::shared_ptr<Engine::Drawable>> _enginesDrawableHowToPlayBonus;
    std::shared_ptr<Engine::Drawable> _enginesPowerUp;
    std::vector<std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>>> _selectorButtons;

    void initEntities() final;
    void initSystems() final;

    public:
    std::vector<std::shared_ptr<Engine::Drawable>> getEnginesDrawable() const;
    int getEnginesDrawableIndex() const;
    void setEnginesDrawableIndex(unsigned char index);
    std::vector<std::shared_ptr<Engine::Drawable>> getEnginesDrawableBonus() const;
    std::shared_ptr<Engine::Drawable> getPowerUpEngine() const;
    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &howToPlay);
void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &menu);

#endif //RTYPE_HOW_TO_PLAY_HPP//
