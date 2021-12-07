/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entity
*/

#include "ecs/entity.hpp"
#include "ecs/component.hpp"
#include <memory>

void rtype::entity::REntity::eachFrame()
{
    if (!_activated)
        return;
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        (*it)->eachFrame();
    }
}

void rtype::entity::REntity::init()
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        (*it)->init();
    }
}

void rtype::entity::REntity::changePos(std::pair<int, int> newPos)
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        auto placeable = dynamic_cast<rtype::component::RPlaceable *>(*it);
        if (placeable)
        {
            placeable->changePos(newPos);
        }
    }
}

void rtype::entity::REntity::unblockInput()
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        auto placeable = dynamic_cast<rtype::component::RMovable *>(*it);
        if (placeable)
        {
            placeable->unBlock();
        }
    }
}

void rtype::entity::REntity::setData(nlohmann::json *j)
{
    _data = j;
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        auto hold = dynamic_cast<rtype::component::RHoldData *>(*it);
        if (hold)
        {
            hold->setData(_data);
        }
    }
}

int rtype::entity::REntity::getData(std::string _data_key)
{
    auto pointer = "/data"_json_pointer;
    return _data->value(pointer / _data_key, 0);
};

std::string rtype::entity::REntity::getDataTxt(std::string _data_key)
{
    auto pointer = "/data_txt"_json_pointer;
    return _data->value(pointer / _data_key, "");
};