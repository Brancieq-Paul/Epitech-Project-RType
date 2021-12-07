/*
** EPITECH PROJECT, 2021
** EntityCreation
** File description:
** EntityCreation
*/

#include "../../../../include/command/commands/udp/sprites/entityCreation.hpp"

EntityCreation::EntityCreation(std::vector<uint8_t> body)
{
    tid = message::uint84ToInt(body[0], body[1], body[2], body[3]);
    sid = message::uint84ToInt(body[4], body[5], body[6], body[7]);
    x = message::uint84ToInt(body[8], body[9], body[10], body[11]);
    y = message::uint84ToInt(body[12], body[13], body[14], body[15]);
    team = body[16];
};

std::vector<message::UDP::responseUDP_t *> EntityCreation::execute(std::shared_ptr<SaloonDB> db)
{
    std::vector<message::UDP::responseUDP_t *> res;
    db->createNewEntity(sid, tid, x, y, team);
    return (res);
};