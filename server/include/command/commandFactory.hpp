/*
** EPITECH PROJECT, 2021
** commandFactory
** File description:
** commandFactory
*/

#ifndef COMMAND_FACTORY_HPP_
#define COMMAND_FACTORY_HPP_

#include "../server/saloons/predictionSystem/saloonDB.hpp"
#include "command.hpp"
#include "../data/message.hpp"

namespace command {
    namespace UDP {
        class IUDPCommand;
    };
    namespace TCP {
        class ITCPCommand;
    };
};

class CommandFactory {

    private:
        CommandFactory() {};
        ~CommandFactory() {};
    public:
        enum CommandTypesUDP {
            SERVER_POSITION_UPDATE = 2,
            SERVER_ENTITY_STATUS_UPDATE = 4,
            CLIENT_VELOCITY_UPDATE = 1,
            CLIENT_ENTITY_CREATION = 3
        };

        enum CommandTypeTCP {
            SERVER_GAME_LAUNCHED = 2,
            SERVER_SALOON_CREATED = 4,
            SERVER_UPDATE_TO_SALOON_COMPOSITION = 6,
            SERVER_DECONNEXION_OF_CLIENT = 8,
            SERVER_UDP_PORT_TO_USE = 13,
            SERVER_SALOON_FULL = 15,
            CLIENT_CREATION_SALOON_ASKED = 3,
            CLIENT_WANT_JOIN_SALOON = 5,
            CLIENT_LEAVE_SALOON = 7,
            CLIENT_READY_TO_PLAY = 9,
            CLIENT_COLLISION_BOX = 12,
            CLIENT_WORLD_BOUNDARIES = 16,
            CLIENT_SCRIPT = 1
        };
        static command::UDP::IUDPCommand *createUDPCommand(message::UDP::messageUDP_t *msg);
        static command::TCP::ITCPCommand *createTCPCommand(message::TCP::messageTCP_t *msg, int idSession);
};

#endif