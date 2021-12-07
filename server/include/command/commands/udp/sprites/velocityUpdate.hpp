/*
** EPITECH PROJECT, 2021
** VelocityUpdate
** File description:
** VelocityUpdate
*/

#ifndef VELOCITY_UPDATE_HPP_
#define VELOCITY_UPDATE_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class VelocityUpdate : public command::UDP::AUDPCommand {
    friend command::UDP::IUDPCommand *CommandFactory::createUDPCommand(message::UDP::messageUDP_t *msg);
    public:
        std::vector<message::UDP::responseUDP_t *> execute(std::shared_ptr<SaloonDB> db);
    protected:
        VelocityUpdate(std::vector<uint8_t> body);
        ~VelocityUpdate() {};
    private:
        int tid;
        int sid;
        int8_t vx;
        int8_t vy;
};

#endif