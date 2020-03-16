/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** main
*/

#include "Server.hpp"

int main()
{
    srand(time(NULL));
    rtype::server::Server server;

    server.mainLoop();
    return 0;
}