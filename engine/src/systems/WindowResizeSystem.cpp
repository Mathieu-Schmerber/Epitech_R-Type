//
// Created by mathi on 06/11/2020.
//

#include "systems/WindowResizeSystem.hpp"
#include "components/ColliderComponent.hpp"
#include "components/ClickableComponent.hpp"

Engine::WindowResizeSystem::WindowResizeSystem(std::shared_ptr<AWindow> &window) : _window(window),
_lastSize(window->getSize()), _baseSize(_lastSize), Engine::System()
{
    this->addDependency<ColliderComponent>();
    this->addDependency<ClickableComponent>();
}

void Engine::WindowResizeSystem::update()
{
    Engine::Point<float> current = this->_window->getSize();
    auto ratio = Scale<float>{(float)(current.x / _baseSize.x),
                               (float)(current.y / _baseSize.y)};

    if (current == this->_lastSize)
        return;
    this->_lastSize = current;
    for (auto &e : this->_entities) {
        auto box = e->getComponent<ColliderComponent>()->getBaseHitBox();
        e->getComponent<ColliderComponent>()->setHitBox(
            {box.x1 * ratio.x, box.x2 * ratio.x, box.y1 * ratio.y, box.y2 * ratio.y}
        );
    }
}