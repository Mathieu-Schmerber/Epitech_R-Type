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
    /*!
     * \brief LobbyComponent constructor
     *
     * Basic PlayerAndStarship
    */
    explicit PlayerAndStarshipComponent() :  Engine::Component() {}
};

#endif //RTYPE_PLAYERANDSTARSHIPCOMPONENT_HPP
