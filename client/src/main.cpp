/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** main
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "myJson.hpp"
#include "ecs/engine.hpp"
#include "error.hpp"

using json = nlohmann::json;

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "USAGE:\n\tr-type-client <ip server>\nDESCRIPTION:\n\t<ip server> : ip of the server\n" << std::endl;
        return 84;
    }
    try {
        rtype::engine::Engine engine;
        std::cout << av[1] << std::endl;
        engine.init(av[1]);
        engine.run(av[1]);
        rtype::clock::RClock::destroy();
    } catch (const Error &e) {
        std::cout << "Error: " << std::string(e.what()) + " | at " << std::string(e.where()) << " in line " << std::to_string(e.on()) << std::endl;
    }
    return 0;
}