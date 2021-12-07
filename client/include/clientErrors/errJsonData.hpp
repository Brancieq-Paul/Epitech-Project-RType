/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** errInexistantFile
*/

#pragma once

#include "error.hpp"

class ErrorJsonData: public Error
{
    public:
        inline ErrorJsonData(std::string desc, const char *file, int line): Error(ConcatOnTheFly() << "Error data in json: " << desc, file, line) {};
};