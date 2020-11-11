//
// Created by mathi on 30/10/2020.
//

#include <sfml/SpriteSfml.hpp>
#include <memory>
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "scenes/HowToPlay.hpp"
#include "entities/ParallaxSlide.hpp"
#include "components/AnimationComponent.hpp"
#include "sfml/MusicSFML.hpp"
#include "entities/Button.hpp"

void fromHowToPlayToMenu(std::shared_ptr<Engine::AScene> &howToPlay)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::MAIN_MENU);

    howToPlay->pushRequest(request);
}

void goToNextHowToPlayScreen(std::shared_ptr<Engine::AScene> &howToPlay)
{
    auto howToPlayObject = std::dynamic_pointer_cast<HowToPlay>(howToPlay);
    auto enginesDrawable = howToPlayObject->getEnginesDrawable();
    auto index = howToPlayObject->getEnginesDrawableIndex();
    auto enginePowerUp = howToPlayObject->getPowerUpEngine();

    if (index == HowToPlayContext::BONUS - 1) {
        for (auto &engines : howToPlayObject->getEnginesDrawableBonus())
            engines->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
    } else {
        for (auto &engines : howToPlayObject->getEnginesDrawableBonus())
            engines->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    }

    if (index == HowToPlayContext::WEAPONS - 1) {
        if (enginePowerUp->getComponent<Engine::SpriteComponent>())
            enginePowerUp->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
    } else {
        enginePowerUp->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    }

    if (enginesDrawable[index] != enginesDrawable.back()) {
        enginesDrawable[index]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
        enginesDrawable[index + 1]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
        howToPlayObject->setEnginesDrawableIndex(index + 1);
    } else {
        fromHowToPlayToMenu(howToPlay);
    }
}

void goToPreviousHowToPlayScreen(std::shared_ptr<Engine::AScene> &howToPlay)
{
    auto howToPlayObject = std::dynamic_pointer_cast<HowToPlay>(howToPlay);
    auto enginesDrawable = howToPlayObject->getEnginesDrawable();
    auto index = howToPlayObject->getEnginesDrawableIndex();
    auto enginePowerUp = howToPlayObject->getPowerUpEngine();

    if (index == HowToPlayContext::BONUS + 1) {
        for (auto &engines : howToPlayObject->getEnginesDrawableBonus())
            engines->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
    } else {
        for (auto &engines : howToPlayObject->getEnginesDrawableBonus())
            engines->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    }

    if (index == HowToPlayContext::WEAPONS + 1) {
        enginePowerUp->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
    } else {
        enginePowerUp->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    }


    if (enginesDrawable[index] != enginesDrawable.front()) {
        enginesDrawable[index]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
        enginesDrawable[index - 1]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
        howToPlayObject->setEnginesDrawableIndex(index - 1);
    } else {
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
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<int>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goToPreviousHowToPlayScreen, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto nextHowToPlayButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> nextHowToPlayButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{GO_NEXT_BUTTON_POSITION_X, GO_NEXT_BUTTON_POSITION_Y}, Engine::Point<int>{GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT}, std::move(nextHowToPlayButtonSprite), &goToNextHowToPlayScreen, std::shared_ptr<Engine::AScene>(this));
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_NEXT_BUTTON_X_IDLE, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_NEXT_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    nextHowToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_NEXT_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});

    auto howToPlaySprite1 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_1_PATH);
    std::shared_ptr<Engine::Entity> howToPlayEngine1 = std::make_shared<Engine::Drawable>(Engine::Point<int>{HOW_TO_PLAY_1_POSITION_X, HOW_TO_PLAY_1_POSITION_Y}, std::move(howToPlaySprite1));
    _enginesDrawableHowToPlayScreen.push_back(howToPlayEngine1);

    auto howToPlaySprite2 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_2_PATH);
    std::shared_ptr<Engine::Entity> howToPlayEngine2 = std::make_shared<Engine::Drawable>(Engine::Point<int>{HOW_TO_PLAY_2_POSITION_X, HOW_TO_PLAY_2_POSITION_Y}, std::move(howToPlaySprite2));
    howToPlayEngine2->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawableHowToPlayScreen.push_back(howToPlayEngine2);

    auto howToPlaySprite3 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_3_PATH);
    std::shared_ptr<Engine::Entity> howToPlayEngine3 = std::make_shared<Engine::Drawable>(Engine::Point<int>{HOW_TO_PLAY_3_POSITION_X, HOW_TO_PLAY_3_POSITION_Y}, std::move(howToPlaySprite3));
    howToPlayEngine3->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawableHowToPlayScreen.push_back(howToPlayEngine3);

    auto howToPlaySprite4 = std::make_unique<SpriteSFML>(HOW_TO_PLAY_4_PATH);
    std::shared_ptr<Engine::Entity> howToPlayEngine4 = std::make_shared<Engine::Drawable>(Engine::Point<int>{HOW_TO_PLAY_4_POSITION_X, HOW_TO_PLAY_4_POSITION_Y}, std::move(howToPlaySprite4));
    howToPlayEngine4->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    _enginesDrawableHowToPlayScreen.push_back(howToPlayEngine4);

    auto bonusSprite1 = std::make_unique<SpriteSFML>(BONUS_1_PATH);
    bonusSprite1->setScale({static_cast<float>(BONUS_SCALE_X), static_cast<float>(BONUS_SCALE_Y)});
    std::shared_ptr<Engine::Entity> bonusEngine1 = std::make_shared<Engine::Drawable>(Engine::Point<int>{BONUS_1_POSITION_X, BONUS_1_POSITION_Y}, std::move(bonusSprite1));
    bonusEngine1->addComponent<Engine::AnimationComponent>(0.4);
    bonusEngine1->getComponent<Engine::AnimationComponent>()->addAnimation(0, {
        {{0, 0}, {BONUS_1_WIDTH, BONUS_1_HEIGHT}},
        {{BONUS_1_WIDTH, 0}, {BONUS_1_WIDTH, BONUS_1_HEIGHT}},
        {{BONUS_1_WIDTH * 2, 0},{BONUS_1_WIDTH, BONUS_1_HEIGHT}},
        {{BONUS_1_WIDTH * 3, 0},{BONUS_1_WIDTH, BONUS_1_HEIGHT}}
    });
    bonusEngine1->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    bonusEngine1->getComponent<Engine::AnimationComponent>()->setAnimation(0);
    _enginesDrawableHowToPlayBonus.push_back(bonusEngine1);

    auto bonusSprite2 = std::make_unique<SpriteSFML>(BONUS_2_PATH);
    bonusSprite2->setScale({static_cast<float>(BONUS_SCALE_X), static_cast<float>(BONUS_SCALE_Y)});
    std::shared_ptr<Engine::Entity> bonusEngine2 = std::make_shared<Engine::Drawable>(Engine::Point<int>{BONUS_2_POSITION_X, BONUS_2_POSITION_Y}, std::move(bonusSprite2));
    bonusEngine2->addComponent<Engine::AnimationComponent>(0.4);
    bonusEngine2->getComponent<Engine::AnimationComponent>()->addAnimation(1, {
        {{0, 0}, {BONUS_2_WIDTH, BONUS_2_HEIGHT}},
        {{BONUS_2_WIDTH, 0}, {BONUS_2_WIDTH, BONUS_2_HEIGHT}},
        {{BONUS_2_WIDTH * 2, 0},{BONUS_2_WIDTH, BONUS_2_HEIGHT}},
        {{BONUS_2_WIDTH * 3, 0},{BONUS_2_WIDTH, BONUS_2_HEIGHT}}
    });
    bonusEngine2->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    bonusEngine2->getComponent<Engine::AnimationComponent>()->setAnimation(1);
    _enginesDrawableHowToPlayBonus.push_back(bonusEngine2);

    auto bonusSprite3 = std::make_unique<SpriteSFML>(BONUS_3_PATH);
    bonusSprite3->setScale({static_cast<float>(BONUS_SCALE_X), static_cast<float>(BONUS_SCALE_Y)});
    std::shared_ptr<Engine::Entity> bonusEngine3 = std::make_shared<Engine::Drawable>(Engine::Point<int>{BONUS_3_POSITION_X, BONUS_3_POSITION_Y}, std::move(bonusSprite3));
    bonusEngine3->addComponent<Engine::AnimationComponent>(0.4);
    bonusEngine3->getComponent<Engine::AnimationComponent>()->addAnimation(2, {
        {{0, 0}, {BONUS_3_WIDTH, BONUS_3_HEIGHT}},
        {{BONUS_3_WIDTH, 0}, {BONUS_3_WIDTH, BONUS_3_HEIGHT}},
        {{BONUS_3_WIDTH * 2, 0},{BONUS_3_WIDTH, BONUS_3_HEIGHT}},
        {{BONUS_3_WIDTH * 3, 0},{BONUS_3_WIDTH, BONUS_3_HEIGHT}}
    });
    bonusEngine3->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    bonusEngine3->getComponent<Engine::AnimationComponent>()->setAnimation(2);
    _enginesDrawableHowToPlayBonus.push_back(bonusEngine3);

    auto powerUpSprite = std::make_unique<SpriteSFML>(POWER_UP_PATH);
    powerUpSprite->setScale({static_cast<float>(POWER_UP_SCALE_X), static_cast<float>(POWER_UP_SCALE_Y)});
    std::shared_ptr<Engine::Entity> enginesPowerUp = std::make_shared<Engine::Drawable>(Engine::Point<int>{POWER_UP_POSITION_X, POWER_UP_POSITION_Y}, std::move(powerUpSprite));
    enginesPowerUp->addComponent<Engine::AnimationComponent>(0.4);
    enginesPowerUp->getComponent<Engine::AnimationComponent>()->addAnimation(3, {
        {{0, 0}, {POWER_UP_WIDTH, POWER_UP_HEIGHT}},
        {{POWER_UP_WIDTH, 0}, {POWER_UP_WIDTH, POWER_UP_HEIGHT}},
        {{POWER_UP_WIDTH * 2, 0},{POWER_UP_WIDTH, POWER_UP_HEIGHT}},
        {{POWER_UP_WIDTH * 3, 0},{POWER_UP_WIDTH, POWER_UP_HEIGHT}}
    });
    enginesPowerUp->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    enginesPowerUp->getComponent<Engine::AnimationComponent>()->setAnimation(3);
    _enginesPowerUp = enginesPowerUp;

    this->spawnEntity(howToPlayEngine1);
    this->spawnEntity(howToPlayEngine2);
    this->spawnEntity(howToPlayEngine3);
    this->spawnEntity(howToPlayEngine4);
    this->spawnEntity(goBackButtonEngine);
    this->spawnEntity(nextHowToPlayButtonEngine);
    this->spawnEntity(bonusEngine1);
    this->spawnEntity(bonusEngine2);
    this->spawnEntity(bonusEngine3);
    this->spawnEntity(enginesPowerUp);
}

void HowToPlay::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(window));
}

std::shared_ptr<Engine::AWindow> HowToPlay::getWindow() const
{
    return _window;
}

std::vector<std::shared_ptr<Engine::Entity>> HowToPlay::getEnginesDrawable() const
{
    return _enginesDrawableHowToPlayScreen;
}

int HowToPlay::getEnginesDrawableIndex() const
{
    return _enginesDrawableHowToPlayScreenIndex;
}

void HowToPlay::setEnginesDrawableIndex(unsigned char index)
{
    _enginesDrawableHowToPlayScreenIndex = index;
}

std::vector<std::shared_ptr<Engine::Entity>> HowToPlay::getEnginesDrawableBonus() const
{
    return _enginesDrawableHowToPlayBonus;
}

std::shared_ptr<Engine::Entity> HowToPlay::getPowerUpEngine() const
{
    return _enginesPowerUp;
}

void HowToPlay::onFocus()
{
    auto enginesDrawable = getEnginesDrawable();

    enginesDrawable[0]->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);
    for (auto it = enginesDrawable.begin() + 1; it != enginesDrawable.end(); it++ ) {
        (*it)->getComponent<Engine::SpriteComponent>()->hasToBeDraw(false);
    }
    setEnginesDrawableIndex(0);
}
