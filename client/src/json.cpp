/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** json
*/

#include "myJson.hpp"
#include "clientErrors/errInexistantFile.hpp"
#include <fstream>

std::string rtype::Json::readDataFromFile(std::string file)
{
    std::ifstream content(file);
    std::ostringstream buff;
    std::string all;

    content.open(file);
    if (content.is_open() != false) {
        buff << content.rdbuf();
        all = buff.str();
    } else {
        throw ErrorInexistantFile(file, __FILE__, __LINE__);
    }
    content.close();
    return all;
}

rtype::Json *rtype::Json::parseFromFile(std::string file)
{
    std::string raw = readDataFromFile(file);
    return (new rtype::Json(rtype::Json::parse(raw)));
}