//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_PLAYERSYSTEM_HPP
#define RTYPE_PLAYERSYSTEM_HPP

#include "ecs/System.hpp"
#include "entities/Player.hpp"
#include "Game.hpp"

class PlayerSystem : public Engine::System
{
private:
    std::map<int, std::pair<std::string, std::vector<Engine::Box<double>>>> _chargeTypes = {
            {1, {"../../client/assets/images/weapons/shot_1_16x4_16x4.png",{
                {{0, 0}, {16, 4}}}}},
            {3, {"../../client/assets/images/weapons/shot_2_36x14_18x14.png",{
                {{0, 0}, {18, 14}},
                {{18, 0}, {18, 14}}}}},
            {5, {"../../client/assets/images/weapons/shot_3_68x14_34x14.png",{
                {{0, 0}, {34, 14}},
                {{34, 0}, {34, 14}}}}},
            {7, {"../../client/assets/images/weapons/shot_4_100x16_50x16.png",{
                {{0, 0}, {50, 16}},
                {{50, 0}, {50, 16}}}}},
            {9, {"../../client/assets/images/weapons/shot_5_132x16_66x16.png",{
                {{0, 0}, {66, 16}},
                {{66, 0}, {66, 16}}}}},
            {10, {"../../client/assets/images/weapons/shot_6_164x18_82x18.png",{
                {{0, 0}, {82, 18}},
                {{82, 0}, {82, 18}}}}},
    };
    std::shared_ptr<Game> _game;
    std::map<int, std::shared_ptr<Engine::ATexture>> _projectileTextures;
    std::shared_ptr<Engine::ATexture> _shootParticle;

    [[nodiscard]] static bool willExitScreen(Engine::Point<double> pos, Engine::Vector<double> dir);
    static void handleMoveAnimations(std::shared_ptr<Engine::Entity> &player, Engine::Vector<double> dir);
    static void handleMovements(std::shared_ptr<Engine::Entity> &player);

    void spawnShootParticle(std::shared_ptr<Engine::Entity> &player);
    void destroyShootParticle(std::shared_ptr<Engine::Entity> &player);
    std::shared_ptr<Engine::Entity> generateProjectile(ManualWeaponComponent *weapon);
    void handleWeapon(std::shared_ptr<Engine::Entity> &player);

    static void handleCollisions(std::shared_ptr<Engine::Entity> &player);
public:
    explicit PlayerSystem(std::shared_ptr<Game> &game);

    void update() override;
};

#endif //RTYPE_PLAYERSYSTEM_HPP