/*
** EPITECH PROJECT, 2021
** asioSession
** File description:
** asioSession
*/

#include "../../include/command/commandFactory.hpp"
#include "../../include/command/commands/tcp/saloon/creationSaloonAsked.hpp"
#include "../../include/command/commands/tcp/saloon/clientWantJoinSaloon.hpp"
#include "../../include/command/commands/tcp/saloon/clientReadyToPlay.hpp"
#include "../../include/command/commands/tcp/saloon/clientLeaveSaloon.hpp"
#include "../../include/command/commands/udp/sprites/entityCreation.hpp"
#include "../../include/command/commands/udp/sprites/velocityUpdate.hpp"
#include "../../include/command/commands/tcp/dataLoading/collisionbox.hpp"
#include "../../include/command/commands/tcp/dataLoading/worldBoundaries.hpp"
#include "../../include/command/commands/tcp/dataLoading/scripts.hpp"

command::UDP::IUDPCommand *CommandFactory::createUDPCommand(message::UDP::messageUDP_t *msg)
{

    switch (msg->id)
    {
    case CommandFactory::CLIENT_VELOCITY_UPDATE:
        return (new VelocityUpdate(msg->body));
    case CommandFactory::CLIENT_ENTITY_CREATION:
        return (new EntityCreation(msg->body));
    default:
        return (nullptr);
    }
};

command::TCP::ITCPCommand *CommandFactory::createTCPCommand(message::TCP::messageTCP_t *msg, int idSession)
{
    switch (msg->id)
    {
    case CommandFactory::CLIENT_CREATION_SALOON_ASKED:
        return (new CreationSaloonAsked(msg->body, idSession));
    case CommandFactory::CLIENT_WANT_JOIN_SALOON:
        return (new ClientWantJoinSaloon(msg->body, idSession));
    case CommandFactory::CLIENT_LEAVE_SALOON:
        return (new ClientLeaveSaloon(msg->body));
    case CommandFactory::CLIENT_READY_TO_PLAY:
        return (new ClientReadyToPLay(msg->body, idSession));
    case CommandFactory::CLIENT_COLLISION_BOX:
        return (new CollisionBox(msg->body));
    case CommandFactory::CLIENT_WORLD_BOUNDARIES:
        return (new WorldBoundaries(msg->body));
    case CommandFactory::CLIENT_SCRIPT:
        return (new MovScripts(msg->body));
    default:
        return (nullptr);
    }
};