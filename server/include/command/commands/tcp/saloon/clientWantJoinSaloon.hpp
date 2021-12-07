/*
** EPITECH PROJECT, 2021
** ClientWantJoinSaloon
** File description:
** ClientWantJoinSaloon
*/

#ifndef CLIENT_WANT_JOIN_ASKED_HPP_
#define CLIENT_WANT_JOIN_ASKED_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"
#include "../../../../server/saloons/saloonManager.hpp"

class ClientWantJoinSaloon : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        ClientWantJoinSaloon(std::vector<uint8_t> body, int idSession);
        ~ClientWantJoinSaloon() {};
    private:
        uint8_t idSaloon;
        std::string pseudo;
        int idSes;
};

#endif