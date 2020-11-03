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


class HowToPlay : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;
    std::vector<Engine::Drawable *> _enginesDrawable;
    unsigned char _enginesDrawableIndex = 0;

    void initEntities() final;
    void initSystems() final;

    public:
    std::vector<Engine::Drawable *> getEnginesDrawable() const;
    unsigned char getEnginesDrawableIndex() const;
    void setEnginesDrawableIndex(unsigned char index);
    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &howToPlay);
void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &menu);

#endif //RTYPE_HOW_TO_PLAY_HPP//
