/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RCollider
*/

#include "component.hpp"
#include "errJsonData.hpp"
#include "userDatabase.hpp"
#include "SfmlUDP.hpp"
#include "message.hpp"

void rtype::component::RCollider::initServerType(int type, nlohmann::json json)
{
    int dim_x;
    int dim_y;
    int hash_layers = 0;
    nlohmann::json def = json["def"];
    auto layers = def["layers"].get<std::vector<int>>();

    std::cout << json.dump() << std::endl;
    dim_x = def.value("/dim_x"_json_pointer, -1);
    if (dim_x == -1)
    {
        throw ErrorJsonData("Path to dim_x invalid.", __FILE__, __LINE__);
    }
    dim_y = def.value("/dim_y"_json_pointer, -1);
    if (dim_y == -1)
    {
        throw ErrorJsonData("Path to dim_y invalid.", __FILE__, __LINE__);
    }
    for (auto it = layers.begin(); it != layers.end(); it++)
    {
        hash_layers += pow(*it, 2);
    }
    std::vector<std::string> _stringBody;
    std::vector<uint8_t> _byteBody;

    std::vector<uint8_t> tmpType = message::intToUint8(type);
    std::vector<uint8_t> tmpDimX= message::intToUint8(dim_x);
    std::vector<uint8_t> tmpDimY = message::intToUint8(dim_y);
    std::vector<uint8_t> tmpHash = message::intToUint8(hash_layers);

    for (int i = 0; i != 4; i++)
        _byteBody.emplace_back(tmpType.at(i));
    for (int i = 0; i != 4; i++)
        _byteBody.emplace_back(tmpDimX.at(i));
    for (int i = 0; i != 4; i++)
        _byteBody.emplace_back(tmpDimY.at(i));
    for (int i = 0; i != 4; i++)
        _byteBody.emplace_back(tmpHash.at(i));
    rtype::sendmfactory::Imessage *message = rtype::network::SfmlUDP::getFactory()->createTCPMessage(rtype::sendmfactory::SendConfigType, _byteBody, _stringBody);
    rtype::network::SfmlTCP::writeData(message->getMessageTCP());
}
