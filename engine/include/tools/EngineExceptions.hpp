/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ENGINEEXCEPTIONS_HPP
#define RTYPE_ENGINEEXCEPTIONS_HPP

#include <iostream>

namespace Engine {

    class EngineException : public std::exception {
    public:
        explicit EngineException(std::string component = "Component: ", std::string message = "An error occurred.") :
        _component(std::move(component)), _message(std::move(message)) {};

        [[nodiscard]] std::string const &getComponent() const
        { return this->_component; };

        [[nodiscard]] const char *what() const noexcept override
        {
            return this->_message.c_str();
        };

    private:
        std::string _component;
        std::string _message;
    };

    class FatalError : public EngineException {
    public:
        explicit FatalError(std::string const &component = "Fatal Error: ",
                            std::string const &message = "A fatal error occured.") : EngineException(component, message)
        {};
    };

    class ServerError : public EngineException {
    public:
        explicit ServerError(std::string const &component = "Server: ",
                             std::string const &message = "An error occurred.") : EngineException(component, message)
        {};

    };

}

#endif //RTYPE_ENGINEEXCEPTIONS_HPP
