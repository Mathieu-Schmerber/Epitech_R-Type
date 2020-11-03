//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "scenes/HowToPlay.hpp"
#include "entities/Button.hpp"
#include "entities/ParallaxSlide.hpp"
#include "components/AnimationComponent.hpp"
#include "tools/Geometry.hpp"
#include "sfml/MusicSFML.hpp"
#include "entities/Music.hpp"

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &howToPlay)
{
    std::dynamic_pointer_cast<HowToPlay>(howToPlay)->setEnginesDrawableIndex(0);
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::MAIN_MENU);

    howToPlay->pushRequest(request);
}

void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &howToPlay)
{
    auto howToPlayObject = std::dynamic_pointer_cast<HowToPlay>(howToPlay);
    auto enginesDrawable = howToPlayObject->getEnginesDrawable();
    auto index = howToPlayObject->getEnginesDrawableIndex();

    if ( enginesDrawable[index] != enginesDrawable.back()) {
        enginesDrawable[index]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
        enginesDrawable[index + 1]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
        howToPlayObject->setEnginesDrawableIndex(index + 1);
    } else {
        enginesDrawable[0]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
        for (auto it = enginesDrawable.begin() + 1; it != enginesDrawable.end(); it++ ) {
            (*it)->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
        }
        fromHowToPlayToMenu(howToPlay);
    }
}

HowToPlay::HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
    : _window(window), _events(events), Engine::AScene(SceneType::HOW_TO_PLAY)
{
    this->initSystems();
    this->initEntities();
}

void HowToPlay::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    auto goBackButtonEngine = new Engine::Button({GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, std::move(goBackButtonSprite), &fromHowToPlayToMenu, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto nextHowToPlayButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    auto nextHowToPlayButtonEngine = new Engine::Button({GO_NEXT_BUTTON_POSITION_X, GO_NEXT_BUTTON_POSITION_Y}, std::move(nextHowToPlayButtonSprite), &goToNextHowToPlayScreen, std::shared_ptr<Engine::AScene>(this));
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({GO_NEXT_BUTTON_X_IDLE, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({GO_NEXT_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({GO_NEXT_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});

    auto howToPlaySprite1 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_1_PATH);
    auto howToPlayEngine1 = new Engine::Drawable({HOW_TO_PLAY_1_POSITION_X, HOW_TO_PLAY_1_POSITION_Y}, std::move(howToPlaySprite1));
    _enginesDrawable.push_back(howToPlayEngine1);

    auto howToPlaySprite2 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_2_PATH);
    auto howToPlayEngine2 = new Engine::Drawable({HOW_TO_PLAY_2_POSITION_X, HOW_TO_PLAY_2_POSITION_Y}, std::move(howToPlaySprite2));
    howToPlayEngine2->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawable.push_back(howToPlayEngine2);

    auto howToPlaySprite3 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_3_PATH);
    auto howToPlayEngine3 = new Engine::Drawable({HOW_TO_PLAY_3_POSITION_X, HOW_TO_PLAY_3_POSITION_Y}, std::move(howToPlaySprite3));
    howToPlayEngine3->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawable.push_back(howToPlayEngine3);

    auto howToPlaySprite4 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_4_PATH);
    auto howToPlayEngine4 = new Engine::Drawable({HOW_TO_PLAY_4_POSITION_X, HOW_TO_PLAY_4_POSITION_Y}, std::move(howToPlaySprite4));
    howToPlayEngine4->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawable.push_back(howToPlayEngine4);

    this->spawnEntity(std::shared_ptr<Engine::Drawable>(howToPlayEngine1));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(howToPlayEngine2));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(howToPlayEngine3));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(howToPlayEngine4));
    this->spawnEntity(std::shared_ptr<Engine::Button>(goBackButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(nextHowToPlayButtonEngine));
}

void HowToPlay::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(music));
}

std::shared_ptr<Engine::AWindow> HowToPlay::getWindow() const
{
    return _window;
}

std::vector<Engine::Drawable *> HowToPlay::getEnginesDrawable() const
{
    return _enginesDrawable;
}

unsigned char HowToPlay::getEnginesDrawableIndex() const
{
    return _enginesDrawableIndex;
}

void HowToPlay::setEnginesDrawableIndex(unsigned char index)
{
    _enginesDrawableIndex = index;
}
