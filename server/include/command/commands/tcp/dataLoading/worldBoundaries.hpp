/*
** EPITECH PROJECT, 2021
** WorldBoundaries
** File description:
** WorldBoundaries
*/

#ifndef WORLD_BOUNDARIES_HPP_
#define WORLD_BOUNDARIES_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class WorldBoundaries : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        WorldBoundaries(std::vector<uint8_t> body);
        ~WorldBoundaries() {};
    private:
        int x;
        int y;
};

#endif