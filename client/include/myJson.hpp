/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** myJson
*/

#ifndef MYJSON_HPP_
#define MYJSON_HPP_

#include <nlohmann/json.hpp>
#include <iostream>

namespace rtype
{
    class Json : public nlohmann::json
    {
    public:
        inline Json() : nlohmann::json() {};
        inline Json(nlohmann::json data) : nlohmann::json(data) {};
        inline ~Json() {};

        static Json *parseFromFile(std::string file);

        static std::string readDataFromFile(std::string file);
    };
}

#endif /* !MYJSON_HPP_ */
