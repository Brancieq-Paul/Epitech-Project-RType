/*
** EPITECH PROJECT, 2021
** ClientReadyToPLay
** File description:
** ClientReadyToPLay
*/

#ifndef CLIENT_READY_TO_PLAY_HPP_
#define CLIENT_READY_TO_PLAY_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class ClientReadyToPLay : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        ClientReadyToPLay(std::vector<uint8_t> body, int idSession);
        ~ClientReadyToPLay() {};
    private:
        bool ready;
        int id;
};

#endif