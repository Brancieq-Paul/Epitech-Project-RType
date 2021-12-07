/*
** EPITECH PROJECT, 2021
** CreationSaloonAsked
** File description:
** CreationSaloonAsked
*/

#include "../../../../include/command/commands/tcp/saloon/creationSaloonAsked.hpp"

CreationSaloonAsked::CreationSaloonAsked(std::vector<uint8_t> body, int idSession)
{

    for (int i = 0; i < body.size() && i < 10; i++)
    {
        pseudo.push_back(body[i]);
    }
    id = idSession;
};

std::vector<message::TCP::responseTCP_t *> CreationSaloonAsked::execute(Saloon *saloon, SaloonManager *manager)
{

    UNUSED(saloon);
    std::vector<message::TCP::responseTCP_t *> res;
    std::vector<message::TCP::responseTCP_t *> toManager;
    if (manager != NULL) {
        std::shared_ptr<Saloon> sal = manager->createNewSaloon(id);
        if (sal != NULL)
        {
            sal->getDB()->addPseudo(pseudo);
            res.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerSaloonCreated(sal->getIDSaloon()));
            sal->respondTCP(res);
            return (toManager);
        }
        else
            toManager.emplace_back(Generator::TCP::ResponseGeneratorTCP::generateServerSaloonFull(id));
    }
    return (toManager);
};