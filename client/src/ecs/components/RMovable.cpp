/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RDrawable
*/

#include "ecs/component.hpp"
#include "utility.hpp"
#include <map>
#include "eventHandler.hpp"
#include <string>
#include "errJsonData.hpp"


rtype::component::RMovable::RMovable() : RHoldData(), _is_blocked(true), _clock(rtype::clock::RClock(10)) {}

void rtype::component::RMovable::eachFrame()
{
    if (_is_blocked)
        return;
    std::map<rtype::utility::keyCode, std::pair<int, int>> _vector_map{
        {rtype::utility::UP, {0, -1}},
        {rtype::utility::DOWN, {0, 1}},
        {rtype::utility::RIGHT, {1, 0}},
        {rtype::utility::LEFT, {-1, 0}}};
    std::pair<int, int> _res = {0, 0};
    std::vector<uint8_t> _byteBody;

    std::cout << "I'M HERE" << std::endl;

    if (_clock.deadLinePassed())
    {
        _clock.reset();
        for (auto it = _vector_map.begin(); it != _vector_map.end(); it++)
        {
            if (rtype::eventHandler::EventHandler::checkEventKey(it->first))
            {
                _res.first += it->second.first;
                _res.second += it->second.second;
            }
        }
        _res.first *= _velocity.first;
        _res.second *= _velocity.second;

        std::vector<uint8_t> tmpType = message::intToUint8(getData("type"));
        std::vector<uint8_t> tmpId = message::intToUint8(getData("id"));

        for (int i = 0; i != tmpType.size(); i++){
            _byteBody.emplace_back(tmpType[i]);
        }
        for (int i = 0; i != tmpId.size(); i++) {
            _byteBody.emplace_back(tmpId[i]);
        }
        _byteBody.emplace_back(_res.first);
        _byteBody.emplace_back(_res.second);

        // std::cout << "Try to move: {" << _res.first << "; " << _res.second << "}" << std::endl;
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createUDPMessage(rtype::sendmfactory::SpeedEntity, _byteBody);
        rtype::network::SfmlUDP::writeData(message->getMessageUDP());
    }
}

void rtype::component::RMovable::initServerType(int type, nlohmann::json json)
{
    std::vector<uint8_t> tmpType = message::intToUint8(type);
    int vel_x_linear;
    int vel_y_linear;
    int vel_x;
    int vel_y;
    int bound_x;
    int bound_y;
    nlohmann::json def = json["def"];

    bound_x = def.value("/bound_x"_json_pointer, 0);
    bound_y = def.value("/bound_y"_json_pointer, 0);

    vel_x_linear = def.value("/vel_x_linear"_json_pointer, 0);
    vel_y_linear = def.value("/vel_y_linear"_json_pointer, 0);
    std::cout << "TEST TYPE = " << type <<  std::endl;
    if (!(vel_x_linear == 0 && vel_y_linear == 0))
    {
        //send linear
        std::vector<std::string> _stringBody;
        std::vector<uint8_t> _tmpBoundX = message::intToUint8(bound_x);
        std::vector<uint8_t> _tmpBoundY = message::intToUint8(bound_y);
        std::vector<uint8_t> _byteBody;

        std::cout << "BANANA TYPE = " << type <<  std::endl;

        for (int i = 0; i != 4; i++)
            _byteBody.emplace_back(tmpType.at(i));
        _byteBody.emplace_back(2);
        _byteBody.emplace_back(vel_x_linear);
        _byteBody.emplace_back(vel_y_linear);
        for (int i = 0; i != 4; i++)
            _byteBody.emplace_back(_tmpBoundX.at(i));
        for (int i = 0; i != 4; i++)
            _byteBody.emplace_back(_tmpBoundY.at(i));
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::SendScriptType, _byteBody, _stringBody);
        rtype::network::SfmlTCP::writeData(message->getMessageTCP());
    }

    vel_x = def.value("/vel_x"_json_pointer, 0);
    vel_y = def.value("/vel_y"_json_pointer, 0);
    if (!(vel_x == 0 && vel_y == 0))
    {
        std::vector<std::string> _stringBody;
        std::vector<uint8_t> _byteBody;
        for (int i = 0; i != 4; i++)
            _byteBody.emplace_back(tmpType.at(i));
        _byteBody.emplace_back(3);
        rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::SendScriptType, _byteBody, _stringBody);
        rtype::network::SfmlTCP::writeData(message->getMessageTCP());
    }
}
