/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** process
*/

#include "message.hpp"
#include "processor.hpp"
#include "userDatabase.hpp"
#include "SfmlUDP.hpp"

rtype::entity::REntity *rtype::processor::MyProcess::findEntity(uint8_t *data)
{
    int typeId = message::uint84ToInt(data[1], data[2], data[3], data[4]);
    int ownId = message::uint84ToInt(data[5], data[6], data[7], data[8]);

    std::cout << "TYPE = " << typeId << std::endl;
    std::cout << "ID = " << ownId << std::endl;

    for (auto it = _entity_list->begin(); it != _entity_list->end(); it++)
    {
        if (it->getData("type") == typeId && it->getData("id") == ownId)
        {
            std::cout << "FIND THIS OBJ !!!" << std::endl;
            return &(*it);
        }
        else
        {
            std::cout << "NOT FOUND !!!" << std::endl;
        }
    }
    return nullptr;
}

void rtype::processor::MyProcess::setPosEntity(rtype::entity::REntity *obj, uint8_t *data)
{
    int x = message::uint84ToInt(data[9], data[10], data[11], data[12]);
    int y = message::uint84ToInt(data[13], data[14], data[15], data[16]);
    Verbose::simpleDebugMessageWithColor("pos of object x:'" + std::to_string(x) + "' y:'" + std::to_string(y) + "'", Verbose::RED, true);
    obj->changePos(std::pair<int, int>(x, y));
}

void rtype::processor::MyProcess::setLife(rtype::entity::REntity *obj, uint8_t *data)
{
    int life = message::uint84ToInt(data[9], data[10], data[11], data[12]);
    if (life <= 0) {
        // std::cout << "TYPE = " << obj->getData("type") << std::endl;
        obj->deactivate();
    }
}

void rtype::processor::MyProcess::processUDP(uint8_t *data)
{
    rtype::entity::REntity *obj = findEntity(data);
    switch (data[0])
    {
    case PosEntity:
        setPosEntity(obj, data);
        break;
    case StatusEntity:
        setLife(obj, data);
        break;
    default:
        break;
    }
}

void rtype::processor::MyProcess::setPlayerInOrder(uint8_t *data)
{
    std::string One;
    std::string Two;
    std::string Three;
    std::string Four;

    for (int i = 0; i != 10; i++) {
        if (data[1 + i] == 0)
            break;
        One += static_cast<char>(data[1 + i]);
    }
    for (int i = 0; i != 10; i++) {
           if (data[11 + i] == 0)
            break;
        Two += static_cast<char>(data[11 + i]);
    }
    for (int i = 0; i != 10; i++) {
           if (data[21 + i] == 0)
            break;
        Three += static_cast<char>(data[21 + i]);
    }
    for (int i = 0; i != 10; i++) {
           if (data[31 + i] == 0)
            break;
        Four += static_cast<char>(data[31 + i]);
    }

    rtype::database::userDatabase::setPlayerName("POne", One);
    rtype::database::userDatabase::setPlayerName("PTwo", Two);
    rtype::database::userDatabase::setPlayerName("PThree", Three);
    rtype::database::userDatabase::setPlayerName("PFour", Four);
    rtype::database::userDatabase::changeNbPlayer(1);

    std::cout << "ULTIME TEST : " << One.compare(rtype::database::userDatabase::getPlayerName("USER")) << std::endl;

    if (One.compare(rtype::database::userDatabase::getPlayerName("USER")) == 0) {
        std::cout << "HERE 1" << std::endl;
        rtype::database::userDatabase::setMyPos(1);
    }
    if (Two.compare(rtype::database::userDatabase::getPlayerName("USER")) == 0) {
        std::cout << "HERE 2 " << std::endl;
        rtype::database::userDatabase::setMyPos(2);
    }
    if (Three.compare(rtype::database::userDatabase::getPlayerName("USER")) == 0)
        rtype::database::userDatabase::setMyPos(3);
    if (Four.compare(rtype::database::userDatabase::getPlayerName("USER")) == 0)
        rtype::database::userDatabase::setMyPos(4);
    std::cout << "MY NAME = |" << rtype::database::userDatabase::getPlayerName("USER") << "|" << std::endl;
    std::cout << "MY TEST NAME = |" << Two << "|" << std::endl;
    std::cout << "MY POS = " << rtype::database::userDatabase::getMyPos() << std::endl;
}

void rtype::processor::MyProcess::setPortUDP(uint8_t *data)
{
    unsigned short port = static_cast<unsigned short>(message::uint84ToInt(data[1], data[2], data[3], data[4]));
    Verbose::showDebugMessage(true);
    rtype::network::SfmlUDP::setPort(port);
    database::userDatabase::setPort(port);
}

void rtype::processor::MyProcess::processTCP(uint8_t *data)
{
    switch (data[0])
    {
    case GameLaunched:
        rtype::database::userDatabase::setGame(true);
        break;
    case IdSalon:
        rtype::database::userDatabase::setIdSalon(data[1]);
        rtype::database::userDatabase::setGoSalon(true);
        break;
    case SomeoneJoinSalon:
        setPlayerInOrder(data);
        break;
    case PortUDP:
        setPortUDP(data);
        rtype::database::userDatabase::setGoSalon(true);
        break;
    case SalonIsFull:
        rtype::database::userDatabase::setFull(data[1]);
        break;

    default:
        break;
    }
    return;
}