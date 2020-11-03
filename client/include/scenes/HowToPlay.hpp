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
#define BONUS_1_POSITION_Y 480
#define BONUS_1_WIDTH 40
#define BONUS_1_HEIGHT 36

#define BONUS_2_PATH "../../client/assets/images/bonus/bonus_2_160x36_40x36.png"
#define BONUS_2_POSITION_X 960
#define BONUS_2_POSITION_Y 480
#define BONUS_2_WIDTH 40
#define BONUS_2_HEIGHT 36

#define BONUS_3_PATH "../../client/assets/images/bonus/bonus_3_160x36_40x36.png"
#define BONUS_3_POSITION_X 1060
#define BONUS_3_POSITION_Y 480
#define BONUS_3_WIDTH 40
#define BONUS_3_HEIGHT 36

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
    std::vector<Engine::Drawable *> _enginesDrawableHowToPlayScreen;
    int _enginesDrawableHowToPlayScreenIndex = 0;
    std::vector<Engine::Drawable *> _enginesDrawableHowToPlayBonus;

    void initEntities() final;
    void initSystems() final;

    public:
    std::vector<Engine::Drawable *> getEnginesDrawable() const;
    int getEnginesDrawableIndex() const;
    void setEnginesDrawableIndex(unsigned char index);
    std::vector<Engine::Drawable *> getEnginesDrawableBonus() const;
    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &howToPlay);
void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &menu);

#endif //RTYPE_HOW_TO_PLAY_HPP//
