/*
** EPITECH PROJECT, 2021
** WorldBoundaries
** File description:
** WorldBoundaries
*/

#include "../../../../include/command/commands/tcp/dataLoading/worldBoundaries.hpp"

std::vector<message::TCP::responseTCP_t *> WorldBoundaries::execute(Saloon *saloon, SaloonManager *manager)
{
    UNUSED(manager);
    std::vector<message::TCP::responseTCP_t *> res;
    if (saloon == NULL)
        return (res);
    saloon->setWroldBoundaries(x, y);
    return (res);
};

WorldBoundaries::WorldBoundaries(std::vector<uint8_t> body){
    x = message::uint84ToUint(body[0], body[1], body[2], body[3]);
    y = message::uint84ToUint(body[4], body[5], body[6], body[7]);
    Verbose::logInError("World boundaries set to '" + std::to_string(x) + "':'" + std::to_string(y) + "'");
};
