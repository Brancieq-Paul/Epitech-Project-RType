/*
** EPITECH PROJECT, 2021
** CollisionBox
** File description:
** CollisionBox
*/

#ifndef COLLISION_BOX_HPP_
#define COLLISION_BOX_HPP_

#include "../../../command.hpp"
#include "../../../commandFactory.hpp"

class CollisionBox : public command::TCP::ATCPCommand {
    friend command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
    public:
        std::vector<message::TCP::responseTCP_t *> execute(Saloon *saloon, SaloonManager *manager);
    protected:
        CollisionBox(std::vector<uint8_t> body);
        ~CollisionBox() {};
    private:
        int dimx;
        int dimy;
        int layers;
        int typeSprite;
};

#endif