/*
** EPITECH PROJECT, 2021
** generateResponses
** File description:
** generateResponses
*/

#include "../../../include/command/generator/generateResponses.hpp"

message::UDP::responseUDP_t *Generator::UDP::ResponseGeneratorUDP::generateServerEntityStatusUpdate(int life, int typeId, int spriteId, uint8_t status)
{
    std::vector<uint8_t> body = message::intToUint8(typeId);
    auto id = message::intToUint8(spriteId);
    auto life_ = message::intToUint8(life);
    body.insert(body.end(), id.begin(), id.end());
    body.insert(body.end(), life_.begin(), life_.end());
    body.emplace_back(status);
    auto msg = message::UDP::createMessage(CommandFactory::SERVER_ENTITY_STATUS_UPDATE, body);
    return (message::UDP::createResponse(msg));
};

message::UDP::responseUDP_t *Generator::UDP::ResponseGeneratorUDP::generateServerPositionUpdate(int x, int y, int typeId, int spriteId)
{
    std::vector<uint8_t> body = message::intToUint8(typeId);
    auto x_ = message::intToUint8(x);
    auto sId = message::intToUint8(spriteId);
    auto y_ = message::intToUint8(y);
    body.insert(body.end(), sId.begin(), sId.end());
    body.insert(body.end(), x_.begin(), x_.end());
    body.insert(body.end(), y_.begin(), y_.end());
    auto msg = message::UDP::createMessage(CommandFactory::SERVER_POSITION_UPDATE, body);
    return (message::UDP::createResponse(msg));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerSaloonFull(int idSession)
{
    std::vector<uint8_t> empty;
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_SALOON_FULL, empty);
    std::vector<std::string> to = {std::to_string(idSession)};
    return (message::TCP::createResponse(msg, to));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerGameLaunched()
{
    std::vector<uint8_t> empty;
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_GAME_LAUNCHED, empty);
    std::vector<std::string> to = {"All"};
    return (message::TCP::createResponse(msg, to));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerSaloonCreated(uint8_t idSaloonCreated)
{

    std::vector<uint8_t> body = {idSaloonCreated};
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_SALOON_CREATED, body);
    std::vector<std::string> to = {"All"};
    return (message::TCP::createResponse(msg, to));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerUpdateToSaloonComposition(std::vector<std::string> names)
{

    std::vector<uint8_t> body;

    for (int j = 0; j < names.size() && j < 4; j++)
    {
        for (int i = 0; i < 10 && i < names[j].size(); i++)
        {
            body.emplace_back(names[j][i]);
        }
    }
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_UPDATE_TO_SALOON_COMPOSITION, body);
    std::vector<std::string> to = {"All"};
    return (message::TCP::createResponse(msg, to));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerDeconnexionOfClient(uint8_t posOfLeaver)
{

    std::vector<uint8_t> body = {posOfLeaver};
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_DECONNEXION_OF_CLIENT, body);
    std::vector<std::string> to = {"All"};
    return (message::TCP::createResponse(msg, to));
};

message::TCP::responseTCP_t *Generator::TCP::ResponseGeneratorTCP::generateServerUDPPortToUse(int port)
{

    std::vector<uint8_t> body = message::intToUint8(port);
    auto msg = message::TCP::createMessage(CommandFactory::SERVER_UDP_PORT_TO_USE, body);
    std::vector<std::string> to = {"All"};
    return (message::TCP::createResponse(msg, to));
};