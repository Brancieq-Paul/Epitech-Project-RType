/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** messageFactory
*/

#include "messageFactory.hpp"

rtype::sendmfactory::Imessage *rtype::sendmfactory::messageFactory::createUDPMessage(TypeMessage type, std::vector<uint8_t> data)
{
    switch (type)
    {
    case SpeedEntity: return (new messageSpeed(data));
        break;
    case CreateEntity: return (new messageCreate(data));
        break;
    default:
        break;
    }
    return nullptr;
}

rtype::sendmfactory::messageSpeed::messageSpeed(std::vector<uint8_t> data)
{
    // std::vector<uint8_t> _byteBody;

    // _byteBody.emplace_back(data.at(1));
    // for (int i = 0; i != 3; i++)
    //     _byteBody.emplace_back(0);
    // _byteBody.emplace_back(data.at(0));
    // for (int i = 0; i != 3; i++)
    //     _byteBody.emplace_back(0);

    // _byteBody.emplace_back(static_cast<uint8_t>(data.at(2)));
    // _byteBody.emplace_back(static_cast<uint8_t>(data.at(3)));
    _messageUDP = message::UDP::createMessage(1, data);
}

rtype::sendmfactory::messageCreate::messageCreate(std::vector<uint8_t> data)
{
    // std::vector<uint8_t> _byteBody;
    // std::vector<uint8_t> typeId = message::intToUint8(data.at(0));
    // std::vector<uint8_t> id = message::intToUint8(data.at(1));
    // _byteBody.emplace_back(data.at(2));
    // _byteBody.emplace_back(data.at(3));
    // _byteBody.emplace_back(static_cast<uint8_t>(data.at(4)));

    // for (int i = 0; i != typeId.size(); i++)
    //     _byteBody.emplace_back(typeId.at(i));
    // for (int i = 0; i != id.size(); i++)
    //     _byteBody.emplace_back(id.at(i));
    _messageUDP = message::UDP::createMessage(3, data);
}