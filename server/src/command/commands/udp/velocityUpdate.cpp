/*
** EPITECH PROJECT, 2021
** VelocityUpdate
** File description:
** VelocityUpdate
*/

#include "../../../../include/command/commands/udp/sprites/velocityUpdate.hpp"

VelocityUpdate::VelocityUpdate(std::vector<uint8_t> body)
{
    tid = message::uint84ToInt(body[0], body[1], body[2], body[3]);
    sid = message::uint84ToInt(body[4], body[5], body[6], body[7]);
    vx = body[8];
    vy = body[9];
}

std::vector<message::UDP::responseUDP_t *> VelocityUpdate::execute(std::shared_ptr<SaloonDB> db)
{
    std::vector<message::UDP::responseUDP_t *> res;
    db->updateEntity(tid, sid, vx, vy);
    return (res);
}