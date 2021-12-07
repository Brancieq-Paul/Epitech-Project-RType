/*
** EPITECH PROJECT, 2021
** CreationSaloonAsked
** File description:
** CreationSaloonAsked
*/

#ifndef CEATION_SALOON_ASKED_HPP_
#define CEATION_SALOON_ASKED_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"
#include "../../../../server/saloons/saloonManager.hpp"

class CreationSaloonAsked : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        CreationSaloonAsked(std::vector<uint8_t> body, int idSession);
        ~CreationSaloonAsked() {};
    private:
        std::string pseudo;
        int id;
};

#endif