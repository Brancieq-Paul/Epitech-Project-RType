/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** entity
*/

#include "entityHandler.hpp"
#include <boost/filesystem.hpp>
#include "errJsonData.hpp"
#include "errInexistantEntityType.hpp"
#include <algorithm>
#include <typeindex>

using recursive_directory_iterator = boost::filesystem::recursive_directory_iterator;

rtype::entity::REntityHandler::REntityHandler(std::string path, bool serverHandle)
{
    init(path, serverHandle);
}

void rtype::entity::REntityHandler::init(std::string path, bool serverHandle)
{
    rtype::Json *j;
    int type = -1;

    for (const auto dirEntry : recursive_directory_iterator(path))
    {
        j = rtype::Json::parseFromFile(dirEntry.path().generic_string());
        type = j->value("/data/type"_json_pointer, -1);
        if (type == -1)
            throw ErrorJsonData("Can't find 'type' integer key in data: '" + path + "'", __FILE__, __LINE__);
        if (entity_def_json_tab_.find(type) != entity_def_json_tab_.end())
            throw ErrorJsonData("Can't create multiple entity template with one type: '" + path + "'", __FILE__, __LINE__);
        entity_def_json_tab_[type] = dirEntry.path().generic_string();
        delete j;
    }
}

void rtype::entity::REntityHandler::initServerTypes()
{
    int type;
    nlohmann::json *j;
    nlohmann::json components;

    for (auto it = entity_def_json_tab_.begin(); it != entity_def_json_tab_.end(); it++)
    {
        type = it->first;
        j = static_cast<nlohmann::json *>(rtype::Json::parseFromFile(entity_def_json_tab_[type]));
        components = (*j)["components"];
        for (auto itc = components.begin(); itc != components.end(); itc++)
        {
            if (itc->value("/type"_json_pointer, "") == "collider")
                rtype::component::RCollider::initServerType(type, *itc);
        }
        for (auto itc = components.begin(); itc != components.end(); itc++)
        {
            if (itc->value("/type"_json_pointer, "") == "movable")
                rtype::component::RMovable::initServerType(type, *itc);
        }
    }
}

void rtype::entity::REntityHandler::createEntity(int type, int id)
{
    nlohmann::json *j;
    nlohmann::json components;
    rtype::entity::REntity enti;

    if (entity_def_json_tab_.find(type) == entity_def_json_tab_.end())
        throw ErrorInexistantEntityType(type, __FILE__, __LINE__);
    j = static_cast<nlohmann::json *>(rtype::Json::parseFromFile(entity_def_json_tab_[type]));
    components = (*j)["components"];
    for (auto it = components.begin(); it != components.end(); it++)
    {
        enti.attach(rtype::component::CompoFactory::makeComponent((*it)));
    }
    enti.setData(j);
    enti.changeData("id", id);
    enti.changeData("type", type);
    enti.init();
    enti._handle_layer = enti.getDataList()->value("/data/handleLayer"_json_pointer, 5);
    enti.activate();
    entity_tab_.push_back(enti);
}

rtype::entity::REntity *rtype::entity::REntityHandler::getEntity(int type, int id)
{
    for (auto it = entity_tab_.begin(); it != entity_tab_.end(); it++)
        if (it->getData("id") == id && it->getData("type") == type)
            return &(*it);
    return nullptr;
}

void rtype::entity::REntityHandler::destroyEntity(int type, int id)
{
    for (auto it = entity_tab_.begin(); it != entity_tab_.end(); it++)
        if (it->getData("type") == type && it->getData("id") == id)
            it = entity_tab_.erase(it);
}

void rtype::entity::REntityHandler::eachFrame()
{
    for (int i = 0; i != 11; i++)
        for (auto it = entity_tab_.begin(); it != entity_tab_.end(); it++)
            if (it->_handle_layer == i)
                it->eachFrame();
}