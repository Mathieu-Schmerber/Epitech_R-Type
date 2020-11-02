/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Emilien
*/

#include "Client.hpp"

Client::Client(std::shared_ptr<Session> &session) : _session(session) {}