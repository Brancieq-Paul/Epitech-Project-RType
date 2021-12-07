/*
** EPITECH PROJECT, 2020
** Error
** File description:
** Error
*/

#ifndef ERR_USAGE_HPP_
#define ERR_USAGE_HPP_

#include "../error.hpp"

class ErrorUsage: public Error {
    public:
        ErrorUsage() : Error("USAGE:\n\tr-type_serveur (verbose==true)\n\nDESCRIPTION:\n\tverbose==true\tThe server will print more infos\n", __FILE__, __LINE__) {};
};
#endif