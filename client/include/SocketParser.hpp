/*!
 * @file SocketParser.hpp
 * @brief SocketParser declaration
 * @authors Matthieu.S
 * @version 1.0
 * @date 14/11/2020
 *
 * The class if useful to parse socket communication
*/

#ifndef RTYPE_SOCKETPARSER_HPP
#define RTYPE_SOCKETPARSER_HPP

#include <vector>
#include "graphical/AFont.hpp"
#include "graphical/ATexture.hpp"
#include "ecs/Entity.hpp"
#include "enumerations/Inputs.hpp"
#include "tools/AssetPool.hpp"
#include "tools/Timer.hpp"
#include "tools/Geometry.hpp"
#include <map>
#include <string>

class SocketParser
{
private:
    std::unique_ptr<Engine::AssetPool> _pool;
    std::unique_ptr<Engine::Timer> _timer;
    std::unique_ptr<Engine::Timer> _serverTimer;
    double _serverDelta;
    double _deltatime;
    bool _serverUpdate;
    std::map<std::string, std::shared_ptr<Engine::ATexture>> _textures;
    std::map<std::string, std::shared_ptr<Engine::AFont>> _fonts;

    [[nodiscard]] static Engine::Point<int> lerp(Engine::Point<int> a, Engine::Point<int> b, double time);
    [[nodiscard]] static bool shouldTeleport(Engine::Point<int> a, Engine::Point<int> b, Engine::Point<int> size);

public:
    /*!
    * \brief SocketParser constructor
    *
    * Set default value to SockerParser member variables
   */
    SocketParser();

    [[nodiscard]] static std::vector<int> parseUdpInputs(int clientId,
                                                         const std::vector<Engine::Inputs> &pressed,
                                                         const std::vector<Engine::Inputs> &released);

    [[nodiscard]] std::shared_ptr<Engine::Entity> unparseUdpEntity(const std::vector<int> &in);
    void updateEntityFromUdp(std::shared_ptr<Engine::Entity> entity, const std::vector<int> &in) const;

    [[nodiscard]] static std::shared_ptr<Engine::Entity> unparseTcpLobby(const std::vector<int> &in);
    static void updateLobbyFromTcp(std::shared_ptr<Engine::Entity> &lobby, const std::vector<int> &in);

    void refreshTimer(bool dataChanged);
    [[nodiscard]] std::shared_ptr<Engine::Entity> createSpriteEntity(const std::vector<int> &in);
    [[nodiscard]] std::shared_ptr<Engine::Entity> createTextEntity(const std::vector<int> &in);
    void updateSpriteEntity(const std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in) const;
    void updateTextEntity(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in) const;
};


#endif //RTYPE_SOCKETPARSER_HPP
