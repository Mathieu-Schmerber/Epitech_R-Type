//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_NETWORKCOMPONENT_HPP
#define RTYPE_NETWORKCOMPONENT_HPP

#include "tools/Geometry.hpp"
#include "ecs/Component.hpp"
#include <vector>

namespace Engine {

    /*!
     * @brief This component stores all the data needed to identify an Engine::Entity over the internet
     */
    class NetworkComponent : public Engine::Component {
    private:
        int _networkIdentity;

    public:
        explicit NetworkComponent(int id = 0) : _networkIdentity(id), Component() {}

        void setNetworkId(int id) {this->_networkIdentity = id;}
        [[nodiscard]] int getNetworkId() const {return this->_networkIdentity;}
    };

}

#endif //RTYPE_NETWORKCOMPONENT_HPP