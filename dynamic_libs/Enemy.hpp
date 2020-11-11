/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ENEMY_HPP
#define RTYPE_ENEMY_HPP

#include <iostream>
#include "../server/game/IEnemy.hpp"

class Enemy : public IEnemy {
private:
    std::string _test;

public:
    Enemy(std::string test = "coucou");

    void test2() override {
        std::cout << "test function call" << std::endl;
        //std::cout << _test << std::endl;
    }
    void hihi() override {
        std::cout << "hihi function call" << std::endl;
    }

};


#endif //RTYPE_ENEMY_HPP
