/*
** EPITECH PROJECT, 2021
** MovScripts
** File description:
** MovScripts
*/

#ifndef MOV_SCRIPT_HPP_
#define MOV_SCRIPT_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class MovScripts : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        MovScripts(std::vector<uint8_t> body);
        ~MovScripts() {};
    private:
        std::vector<uint8_t> data;
        int type_;
        int scripts;
};

#endif