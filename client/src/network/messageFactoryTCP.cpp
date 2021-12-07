/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** messageFactoryTCP
*/

#include "messageFactory.hpp"

rtype::sendmfactory::Imessage *rtype::sendmfactory::messageFactory::createTCPMessage(TypeMessageTCP type, std::vector<uint8_t> dataNb, std::vector<std::string> dataStr)
{
    switch (type)
    {
    case CreateSalon: return (new TCP::messageCreateSalon(dataStr));
        break;
    case JoinSalon: return (new TCP::messageJoinSalon(dataNb, dataStr));
        break;
    case QuitSalon: return (new TCP::messageQuitSalon());
        break;
    case ReadySalon: return (new TCP::messageReadySalon(dataNb));
        break;
    case SendConfigType: return (new TCP::messageSendConfigType(dataNb));
        break;
    case SendScriptType: return (new TCP::messageSendScriptType(dataNb));
        break;
    case SendWindowSize: return (new TCP::messageWindowSize(dataNb));
        break;
    default:
        break;
    }
    return nullptr;
}

rtype::sendmfactory::TCP::messageCreateSalon::messageCreateSalon(std::vector<std::string> dataStr)
{
    std::vector<uint8_t> _byteBody;
    std::cout << "NAME = " << dataStr.at(0) << std::endl;

    _byteBody = message::addStrToUint8Vector(_byteBody, dataStr.at(0), 10);
    _messageTCP = message::TCP::createMessage(3, _byteBody);
}

rtype::sendmfactory::TCP::messageJoinSalon::messageJoinSalon(std::vector<uint8_t> dataNb, std::vector<std::string> dataStr)
{
    std::vector<uint8_t> _byteBody;
    _byteBody.emplace_back(dataNb.at(0));
    _byteBody = message::addStrToUint8Vector(_byteBody, dataStr.at(0), 10);
    _messageTCP = message::TCP::createMessage(5, _byteBody);
}

rtype::sendmfactory::TCP::messageQuitSalon::messageQuitSalon()
{
    std::vector<uint8_t> _byteBody;
    _messageTCP = message::TCP::createMessage(7, _byteBody);
}

rtype::sendmfactory::TCP::messageReadySalon::messageReadySalon(std::vector<uint8_t> dataNb)
{
    std::vector<uint8_t> _byteBody;
    _byteBody.emplace_back(dataNb.at(0));
    _messageTCP = message::TCP::createMessage(9, _byteBody);
}

rtype::sendmfactory::TCP::messageSendConfigType::messageSendConfigType(std::vector<uint8_t> dataNb)
{
    std::vector<uint8_t> _byteBody;

    for (int i = 0; i != 16; i++) {
        _byteBody.emplace_back(dataNb.at(i));
    }
    _messageTCP = message::TCP::createMessage(12, _byteBody);
}

rtype::sendmfactory::TCP::messageSendScriptType::messageSendScriptType(std::vector<uint8_t> dataNb)
{
    // std::vector<uint8_t> _byteBody;

    // for (int i = 0; i; i++) {
    //     _byteBody.emplace_back(dataNb.at(i));
    // }
    _messageTCP = message::TCP::createMessage(1, dataNb);
}

rtype::sendmfactory::TCP::messageWindowSize::messageWindowSize(std::vector<uint8_t> dataNb)
{
    _messageTCP = message::TCP::createMessage(16, dataNb);
}