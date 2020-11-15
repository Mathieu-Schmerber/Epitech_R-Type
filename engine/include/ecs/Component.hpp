//
// Created by mathi on 29/10/2020.
//
#pragma once

#ifndef RTYPE_COMPONENT_HPP
#define RTYPE_COMPONENT_HPP

#include <string>
#include <iostream>

namespace Engine {

    /*!
     * Describes a Component
     */
    class Component {
    protected:
        std::string _info;
    public:
        Component() = default;
        ~Component() = default;

        /*!
         * @brief Sets the component type
         * @param info the component type using typeid()
         */
        void setInfo(const std::string &info) {this->_info = info;}

        /*!
         * @brief Gets the component type
         * @return component type
         */
        [[nodiscard]] std::string getInfo() const {return this->_info;}
    };
}

#endif //RTYPE_COMPONENT_HPP