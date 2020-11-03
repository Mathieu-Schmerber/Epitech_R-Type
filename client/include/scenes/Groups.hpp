//
// Created by mathi on 03/11/2020.
//

#ifndef RTYPE_GROUPS_HPP
#define RTYPE_GROUPS_HPP

#include "sceneManagement/AEntityGroup.hpp"
#include "entities/ParallaxSlide.hpp"
#include "entities/Music.hpp"
#include "sfml/SpriteSfml.hpp"
#include "sfml/MusicSFML.hpp"
#include "components/MusicComponent.hpp"
#include "Layer.hpp"

#define MENU_PARALLAX_PATH "../../client/assets/images/parallax/parallax_3_3840x1080.png"

class ParallaxGroup : public Engine::AEntityGroup {
public:
    ParallaxGroup() : Engine::AEntityGroup() {
        auto menuParralaxA = std::make_unique<SpriteSFML>(MENU_PARALLAX_PATH);
        auto menuParralaxB = std::make_unique<SpriteSFML>(MENU_PARALLAX_PATH);
        auto slideA = new Engine::ParallaxSlide({0, 0}, {-1920, 0}, {-10, 0}, std::move(menuParralaxA));
        auto slideB = new Engine::ParallaxSlide({1920, 0}, {0, 0}, {-10, 0}, std::move(menuParralaxB));

        this->addEntities({std::shared_ptr<Engine::ParallaxSlide>(slideA),
                           std::shared_ptr<Engine::ParallaxSlide>(slideB)});
    }
};

class MusicGroup : public Engine::AEntityGroup {
public:
    MusicGroup() : Engine::AEntityGroup() {
        auto music = std::make_unique<MusicSFML>("../../client/assets/ogg/themes/menu_theme.ogg");
        auto musicE = new Engine::Music(std::move(music));

        this->addEntities({std::shared_ptr<Engine::Music>(musicE)});
    }

    void freeze() override {
        Engine::MusicComponent *music = nullptr;

        for (auto &e : this->getEntities()) {
            music = e->getComponent<Engine::MusicComponent>();
            if (music)
                music->getMusic()->pause();
        }
    }

    void unFreeze() override {
        Engine::MusicComponent *music = nullptr;

        for (auto &e : this->getEntities()) {
            music = e->getComponent<Engine::MusicComponent>();
            if (music)
                music->getMusic()->play();
        }
    }
};

#endif //RTYPE_GROUPS_HPP
