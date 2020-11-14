/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_RANDOMETU_HPP
#define RTYPE_RANDOMETU_HPP

#include <random>
#include <iostream>

namespace Engine {

    class RandomETU {
        public:
        static int randETU() {
            std::random_device rd;
            std::mt19937 gen(rd());
            return static_cast<int>(gen());
        }

        static int randETU(int max) {
            return randETU<int>(0, max);
        }

        template<typename U, typename T>
        static U randETU(T min, T max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(min, max);
            return static_cast<U>(dist(gen));
        }

    };

}

#endif //RTYPE_RANDOMETU_HPP
