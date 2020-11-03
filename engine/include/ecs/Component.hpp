//
// Created by mathi on 29/10/2020.
//
#pragma once

#ifndef RTYPE_COMPONENT_HPP
#define RTYPE_COMPONENT_HPP

#include <string>
#include <iostream>

namespace Engine {

    class Component {
    protected:
        std::string _info;
    public:
        Component() = default;
        ~Component() = default;

        void setInfo(const std::string &info) {this->_info = info;}
        [[nodiscard]] std::string getInfo() const {return this->_info;}
    };
}

#endif //RTYPE_COMPONENT_HPP
