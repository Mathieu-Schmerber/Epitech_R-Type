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

        [[nodiscard]] std::string getFmtMessage() const {
            return "\033[31;1m" + _component + "\033[0;0m: " + _message;
        }

    private:
        std::string _component;
        std::string _message;
    };

    class ServerError : public EngineException {
    public:
        explicit ServerError(std::string const &message = "An error occurred.") : EngineException("ServerError", message)
        {};
    };

    class ConnectError : public EngineException {
    public:
        explicit ConnectError(std::string const &message = "An error occurred.") : EngineException("ConnectionError", message)
        {};
    };

    class DynamicLibError : public EngineException {
    public:
        explicit DynamicLibError(std::string const &message = "An error occurred.") : EngineException("DynamicLibError", message)
        {};
    };

    class ComponentError : public EngineException {
    public:
        explicit ComponentError(std::string const &message = "An error occurred.") : EngineException("ComponentError", message)
        {};
    };

    class SystemError : public EngineException {
    public:
        explicit SystemError(std::string const &message = "An error occurred.") : EngineException("SystemError", message)
        {};
    };

    inline std::ostream &operator<<(std::ostream &st, Engine::EngineException &e)
    {
        return st << e.getFmtMessage();
    }
}



#endif //RTYPE_ENGINEEXCEPTIONS_HPP
