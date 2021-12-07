/*
** EPITECH PROJECT, 2020
** Error
** File description:
** Error
*/

#ifndef ERR_DB_CLOSING_FAILED_HPP_
#define ERR_DB_CLOSING_FAILED_HPP_

#include "../error.hpp"

class ErrorDbClosingFailed: public Error {
    public:
        ErrorDbClosingFailed(const char *file, int line) : Error("Error : The database unsucessfuly closed.", file, line) {};
};
#endif