/*
** EPITECH PROJECT, 2019
** Sans titre(Espace de travail)
** File description:
** client
*/

#include "../includes.hpp"

#include "Display.hpp"
#include "Client.hpp"

int main()
{
    srand(time(NULL));
    rtype::client::Client client;

    client.init();
    client.run();
    return 0;
}