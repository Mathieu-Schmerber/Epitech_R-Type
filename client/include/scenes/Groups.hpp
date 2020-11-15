/*!
 * @file Groups.hpp
 * @brief Contain groups declaration
 * @authors Mathieu.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_GROUPS_HPP
#define RTYPE_GROUPS_HPP

#include <memory>
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
    /*!
     * \brief ParallaxGroup entity constructor
     *
     * Create the group ParallaxGroup, to share parallax between different scene.
    */
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
    /*!
     * \brief MusicGroup entity constructor
     *
     * Create the group MusicGroup, to share music between different scene
    */
    MusicGroup() : Engine::AEntityGroup() {
        auto music = std::make_unique<MusicSFML>("../../client/assets/ogg/themes/menu_theme.ogg");
        auto entity = std::make_shared<Engine::Music>(std::move(music));

        this->addEntities({entity});
    }

    ~MusicGroup() = default;

    /*!
     * \brief MusicGroup freeze method
     *
     * This method permit to pause the actual played music
    */
    void freeze() override {
        Engine::MusicComponent *music = nullptr;

        for (auto &e : this->getEntities()) {
            music = e->getComponent<Engine::MusicComponent>();
            if (music)
                music->getMusic()->pause();
        }
    }

    /*!
     * \brief MusicGroup unfreeze method
     *
     * This method permit to replayed the actual frozen music
    */
    void unFreeze() override {
        Engine::MusicComponent *music = nullptr;

        for (auto &e : this->getEntities()) {
            music = e->getComponent<Engine::MusicComponent>();
            if (music && !music->getMusic()->isStopped())
                music->getMusic()->play(100);
        }
    }
};

#endif //RTYPE_GROUPS_HPP
