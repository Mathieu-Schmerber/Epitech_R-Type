//
// Created by mathi on 03/11/2020.
//

#ifndef RTYPE_SCENEREQUEST_HPP
#define RTYPE_SCENEREQUEST_HPP

#include "enumerations/QueryType.hpp"

namespace Engine {

    class SceneRequest {
    private:
        QueryType _query;
        std::pair<int, std::shared_ptr<Engine::Entity>> _args;

    public:
        SceneRequest(QueryType type, int id, const std::shared_ptr<Engine::Entity> &entity = nullptr) : _query(type), _args({id, entity}) {}

        [[nodiscard]] QueryType type() const {return this->_query;}
        [[nodiscard]] std::pair<int, std::shared_ptr<Engine::Entity>> arguments() const {return this->_args;}
    };

}

#endif //RTYPE_SCENEREQUEST_HPP
