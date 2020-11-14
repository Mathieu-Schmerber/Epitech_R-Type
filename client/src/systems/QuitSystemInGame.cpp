//
// Created by paul on 11/14/20.
//

#include "components/ButtonComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "systems/QuitSystemInGame.hpp"

QuitSystemInGame::QuitSystemInGame(std::shared_ptr<Engine::AEvents> &events,
    std::shared_ptr<Engine::AScene> &scene) : _events(events), _scene(scene), Engine::System()
{
    this->addDependency<Engine::ClickableComponent>();
    this->addDependency<Engine::ButtonComponent>();
    this->addDependency<Engine::SpriteComponent>();
}

void QuitSystemInGame::update()
{
    auto input = this->_events->getKeysReleased();

    if (!input.empty()) {
        if (input.front() == Engine::Inputs::Escape) {
            for (auto &e : _entities) {
                auto quitButton = e->getComponent<Engine::ButtonComponent>();
                if (quitButton) {
                    e->getComponent<Engine::SpriteComponent>()->hasToBeDraw(
                        !e->getComponent<Engine::SpriteComponent>()->getHasToBeDraw()
                    );
                }
            }
        }
    }
}

