//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_HOW_TO_PLAY_HPP
#define RTYPE_HOW_TO_PLAY_HPP

#include "SceneType.hpp"
#include "AScene.hpp"
#include "graphical/AWindow.hpp"
#include "graphical/AEvents.hpp"

#define HOW_TO_PLAY_PATH "../../client/assets/images/background/background_4.png"
#define HOW_TO_PLAY_POSITION_X 0
#define HOW_TO_PLAY_POSITION_Y 0

#define GO_BACK_BUTTON_PATH "../../client/assets/images/buttons/left_arrow/left_arrow_full_192x64.png"
#define GO_BACK_BUTTON_POSITION_X 30
#define GO_BACK_BUTTON_POSITION_Y 30
#define GO_BACK_BUTTON_Y 0
#define GO_BACK_BUTTON_HEIGHT 64
#define GO_BACK_BUTTON_WIDTH 64
#define GO_BACK_BUTTON_X_IDLE 0
#define GO_BACK_BUTTON_X_HOVER 64
#define GO_BACK_BUTTON_X_CLICKED 128

class HowToPlay : public Engine::AScene
{
    private:
    std::shared_ptr<Engine::AWindow> _window;
    std::shared_ptr<Engine::AEvents> _events;

    void initEntities() final;
    void initSystems() final;

    public:

    HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events);
    std::shared_ptr<Engine::AWindow> getWindow() const;
};

void goToMenuScene(std::shared_ptr<Engine::AScene> &menu);

#endif //RTYPE_HOW_TO_PLAY_HPP//
