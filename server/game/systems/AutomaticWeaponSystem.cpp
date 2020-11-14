/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "entities/Projectile.hpp"
#include "components/AutomaticWeaponComponent.hpp"
#include "AutomaticWeaponSystem.hpp"

AutomaticWeaponSystem::AutomaticWeaponSystem(std::shared_ptr<Game> &game) : _game(game)
{
    this->addDependency<Engine::TransformComponent>();
    this->addDependency<AutomaticWeaponComponent>();
    this->addDependency<Engine::SpriteComponent>();
    this->_projectileTexture = std::make_shared<DataTexture>("../../client/assets/images/projectiles/projectile_1_72x18_18x18.png");
}

bool AutomaticWeaponSystem::hasToShoot(AutomaticWeaponComponent *weapon)
{
    return true;
}

std::shared_ptr<Engine::Entity> AutomaticWeaponSystem::generateProjectile(AutomaticWeaponComponent *weapon)
{
    auto type = weapon->getProjectileType();
    auto projectile = std::make_shared<Projectile>(Engine::Point<double>{0, 0}, Engine::Point<double>{22, 18},
                                              weapon->getShotSpeed(), weapon->getCurrentDamages(), 2,
                                              _textures[type], weapon->getProjectileMask());

    projectile->getComponent<Engine::AnimationComponent>()->setFrameTime(0.2);
    projectile->getComponent<Engine::AnimationComponent>()->addAnimation(0, _anims[type]);
    projectile->getComponent<Engine::AnimationComponent>()->setAnimation(0, true);
    projectile->getComponent<Engine::ColliderComponent>()->setHitBox(_anims[type][0]);
    projectile->getComponent<Engine::ColliderComponent>()->setBaseHitBox(_anims[type][0]);
    projectile->getComponent<Engine::SpriteComponent>()->getSprite()->setRect(_anims[type][0]);
    return projectile;
}


void AutomaticWeaponSystem::automaticShot(std::shared_ptr<Engine::Entity> &shooter)
{
    auto weapon = shooter->getComponent<AutomaticWeaponComponent>();
    auto transform = shooter->getComponent<Engine::TransformComponent>();
    auto box1 = Engine::Box<double>{transform->getPos(), shooter->getComponent<Engine::SpriteComponent>()->getSprite()->getRect().size};
    std::shared_ptr<Engine::Entity> proj;

    if (hasToShoot(weapon) && weapon->canShoot()) {
        weapon->refreshShoots();
        proj = this->generateProjectile(weapon);
        auto box2 = Engine::Box<double>{transform->getPos(), proj->getComponent<Engine::SpriteComponent>()->getSprite()->getRect().size};
        proj->getComponent<Engine::TransformComponent>()->setPos(Engine::Geometry::placeForward(box1, box2));
        this->_game->spawn(proj, true);
    }
}

void AutomaticWeaponSystem::update()
{
    for (auto &e : this->_entities) {
        automaticShot(e);
    }
}
