/*!
 * @file PlayerAndStarship.hpp
 * @brief PlayerAndStarship prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_PLAYERANDSTARSHIPCOMPONENT_HPP
#define RTYPE_PLAYERANDSTARSHIPCOMPONENT_HPP

#include "ecs/Entity.hpp"

class PlayerAndStarshipComponent : public Engine::Component {
    public:
        int _id;
    /*!
     * \brief LobbyComponent constructor
     *
     * Basic PlayerAndStarship
    */
    explicit PlayerAndStarshipComponent(int id) :  _id(id), Engine::Component() {}
    [[nodiscard]] int getId() const {return _id;};
    void setId(int id) {_id = id;};

};

#endif //RTYPE_PLAYERANDSTARSHIPCOMPONENT_HPP
