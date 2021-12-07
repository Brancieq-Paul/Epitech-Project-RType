/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** RHoldData
*/

#include "ecs/component.hpp"

int rtype::component::RHoldData::getData(std::string _data_key)
{
    auto pointer = "/data"_json_pointer;
    pointer = pointer / _data_key;
    return _data->value(pointer, 0);
}

std::string rtype::component::RHoldData::getDataTxt(std::string _data_key)
{
    auto pointer = "/data_txt"_json_pointer;
    pointer = pointer / _data_key;
    return _data->value(pointer, "");
}
