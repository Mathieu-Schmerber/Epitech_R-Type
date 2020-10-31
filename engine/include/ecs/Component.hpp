//
// Created by mathi on 29/10/2020.
//
#pragma once

#ifndef RTYPE_COMPONENT_HPP
#define RTYPE_COMPONENT_HPP

namespace Engine {

    class Component {
    public:
        Component() = default;
        virtual ~Component() = 0;
    };
}

#endif //RTYPE_COMPONENT_HPP
