/*
** EPITECH PROJECT, 2021
** ClientLeaveSaloon
** File description:
** ClientLeaveSaloon
*/

#ifndef CLIENT_LEAVE_SALOON_HPP_
#define CLIENT_LEAVE_SALOON_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class ClientLeaveSaloon : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        ClientLeaveSaloon(std::vector<uint8_t> body);
        ~ClientLeaveSaloon() {};
};

#endif