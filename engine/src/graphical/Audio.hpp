/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AUDIO_HPP
#define RTYPE_AUDIO_HPP

#include <type_traits>
#include <graphical/ASound.hpp>
#include <graphical/AMusic.hpp>

namespace Engine {


    template<class T, std::enable_if<
            std::is_same<Engine::ASound, T>::value ||
            std::is_same<Engine::AMusic, T>::value> ||
            std::is_base_of<Engine::ASound, T>::value>>
    class Audio {
    public:
        Audio() = default;
    };

}

#endif //RTYPE_AUDIO_HPP
