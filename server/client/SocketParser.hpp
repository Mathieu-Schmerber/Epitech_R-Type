//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_SOCKETPARSER_HPP
#define RTYPE_SOCKETPARSER_HPP

#include <utility>
#include <vector>
#include "ecs/Entity.hpp"
#include "enumerations/Inputs.hpp"

class SocketParser
{
public:
    [[nodiscard]] static std::pair<std::vector<Engine::Inputs>, std::vector<Engine::Inputs>> unparseUdpInputs(const std::vector<int> &in);
    [[nodiscard]] static std::vector<int> parseUdpEntity(const std::shared_ptr<Engine::Entity>& entity);

    static std::vector<int> parseUdpSprite(const std::shared_ptr<Engine::Entity> &entity);
    static std::vector<int> parseUdpText(const std::shared_ptr<Engine::Entity> &entity);

    enum Type {
        Sprite = 1,
        Text = 2
    };
};

#endif //RTYPE_SOCKETPARSER_HPP
