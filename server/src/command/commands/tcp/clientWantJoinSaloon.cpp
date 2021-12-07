/*
** EPITECH PROJECT, 2021
** ClientWantJoinSaloon
** File description:
** ClientWantJoinSaloon
*/
#include "../../../../include/command/commands/tcp/saloon/clientWantJoinSaloon.hpp"

ClientWantJoinSaloon::ClientWantJoinSaloon(std::vector<uint8_t> body, int idSession)
{

    idSaloon = body[0];
    for (int i = 1; i < 11; i++)
        pseudo.push_back(body[i]);
    idSes = idSession;
};

std::vector<message::TCP::responseTCP_t *> ClientWantJoinSaloon::execute(Saloon *saloon, SaloonManager *manager)
{

    UNUSED(saloon);
    std::vector<message::TCP::responseTCP_t *> res;
    std::vector<message::TCP::responseTCP_t *> toManager;
    if (manager != NULL) {
        auto sal = manager->giveTCPSessionToSaloon(idSaloon, idSes);
        if (sal != nullptr)
        {
            sal->getDB()->addPseudo(pseudo);
            res.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerUDPPortToUse(sal->getUDPPort()));
            sal->respondTCP(res);
            return (toManager);
        }
        else
        {
            toManager.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerSaloonFull(idSes));
        }
    }
    return (toManager);
};