/*
** EPITECH PROJECT, 2021
** ClientReadyToPLay
** File description:
** ClientReadyToPLay
*/

#include "../../../../include/command/commands/tcp/saloon/clientReadyToPlay.hpp"

ClientReadyToPLay::ClientReadyToPLay(std::vector<uint8_t> body, int idSession)
{
    id = idSession;
    if (body[0] == 1)
        ready = true;
    else
        ready = false;
};

std::vector<message::TCP::responseTCP_t *> ClientReadyToPLay::execute(Saloon *saloon, SaloonManager *manager)
{
    std::vector<message::TCP::responseTCP_t *> empty;
    UNUSED(manager);
    if (saloon != NULL)
        saloon->aPlayerWantToPLay(id, ready);
    return (empty);
};
