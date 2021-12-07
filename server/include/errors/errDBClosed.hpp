/*
** EPITECH PROJECT, 2020
** Error
** File description:
** Error
*/

#ifndef ERR_DB_CLOSED_HPP_
#define ERR_DB_CLOSED_HPP_

#include "../error.hpp"

class ErrorDBClosed: public Error {
    public:
        ErrorDBClosed(const char *file, int line) : Error("Error : The database is closed. Impossible to access it.", file, line) {};
};
#endif