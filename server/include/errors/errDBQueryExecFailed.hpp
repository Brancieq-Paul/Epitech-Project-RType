/*
** EPITECH PROJECT, 2020
** Error
** File description:
** Error
*/

#ifndef ERR_DB_QUERY_EXEC_FAILED_HPP_
#define ERR_DB_QUERY_EXEC_FAILED_HPP_

#include "../error.hpp"

class ErrorDbQueryExecFailed: public Error {
    public:
        ErrorDbQueryExecFailed(std::string query, const char *file, int line) : Error(ConcatOnTheFly() << std::string("Error : The following query has failed: ") << query , file, line) {};
};
#endif