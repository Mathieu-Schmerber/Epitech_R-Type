//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_GAME_HPP
#define RTYPE_GAME_HPP

#include <mutex>
#include "entities/Enemy.hpp"
#include "ecs/System.hpp"
#include "tools/Timer.hpp"
#include "networking/UDP/UdpSocketInput.hpp"
#include "Client.hpp"
#include "tools/DLLoader.hpp"
#include "GameData.hpp"

class Game : public std::enable_shared_from_this<Game>
{
private:
    bool _running;
    int _idIncrement;
    std::unique_ptr<Engine::Timer> _timer;
    std::vector<std::unique_ptr<Engine::System>> _systems;
    std::vector<std::shared_ptr<Engine::Entity>> _entities;
    std::vector<std::shared_ptr<Client>> _players;
    std::reference_wrapper<std::unique_ptr<UdpSocketInput>> _reception;
    std::vector<std::shared_ptr<Engine::Entity>> _playersSpaceShips;
    std::vector<std::shared_ptr<Engine::Entity>> _backgrounds;

    void spawnPlayers();
    void initGameEntities();
    void initGameSystems();

public:
    Game(std::vector<std::shared_ptr<Client>> &players, std::unique_ptr<UdpSocketInput> &reception);
    ~Game();

    void setBackground(int nb);
    void spawn(std::shared_ptr<Engine::Entity> entity, bool addToNetwork);
    void despawn(std::shared_ptr<Engine::Entity> &entity);
    void stopTheGame();
    void update();
    [[nodiscard]] bool isGameRunning() const;
    void removeClientInGame(const std::shared_ptr<Client> &cli);
    std::vector<std::shared_ptr<Engine::Entity>> getPlayersSpaceShips() const {return _playersSpaceShips;};
};


#endif //RTYPE_GAME_HPP