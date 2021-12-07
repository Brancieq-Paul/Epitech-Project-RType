/*
** EPITECH PROJECT, 2021
** EntityCreation
** File description:
** EntityCreation
*/

#ifndef ENTITY_CREATION_HPP_
#define ENTITY_CREATION_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class EntityCreation : public command::UDP::AUDPCommand {
    friend command::UDP::IUDPCommand *CommandFactory::createUDPCommand(message::UDP::messageUDP_t *msg);
    public:
        std::vector<message::UDP::responseUDP_t *> execute(std::shared_ptr<SaloonDB> db);
    protected:
        EntityCreation(std::vector<uint8_t> body);
        ~EntityCreation() {};
    private:
        int tid;
        int sid;
        int x;
        int y;
        uint8_t team;
};

#endif