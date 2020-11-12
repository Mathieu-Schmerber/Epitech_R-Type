//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_NETWORKCOMPONENT_HPP
#define RTYPE_NETWORKCOMPONENT_HPP

#include "ecs/Component.hpp"
#include "tools/Geometry.hpp"

namespace Engine {

    class NetworkComponent : public Engine::Component {
    private:
        int _networkIdentity;
        std::vector<float> _dataSaved;

    public:
        explicit NetworkComponent(int id = 0) : _networkIdentity(id), _dataSaved({}), Component() {}

        void setNetworkId(int id) {this->_networkIdentity = id;}
        [[nodiscard]] int getNetworkId() const {return this->_networkIdentity;}

        void saveData(const std::vector<float> &data) {this->_dataSaved = data;}
        [[nodiscard]] std::vector<float> getData() const {return this->_dataSaved;}
    };

}

#endif //RTYPE_NETWORKCOMPONENT_HPP