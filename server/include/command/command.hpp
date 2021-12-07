/*
** EPITECH PROJECT, 2021
** command
** File description:
** command
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include "../server/saloons/saloon.hpp"
#include "../data/message.hpp"
#include <vector>
#include "generator/generateResponses.hpp"


#define UNUSED(x) (void)x

class SaloonManager;

namespace command {

    namespace UDP {
        class IUDPCommand {
            public:
                virtual ~IUDPCommand() = default;

                virtual std::vector<message::UDP::responseUDP_t *> execute(std::shared_ptr<SaloonDB> db) = 0;
        };

        class AUDPCommand : public IUDPCommand {
            protected:
                AUDPCommand() {};
        };
    };

    namespace TCP {
        class ITCPCommand {
            public:
                virtual ~ITCPCommand() = default;

                virtual std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager) = 0;
        };

        class ATCPCommand : public ITCPCommand {
            protected:
                ATCPCommand() {};
        };
    };
};

#endif