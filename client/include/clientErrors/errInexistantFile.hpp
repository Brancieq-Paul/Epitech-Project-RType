/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** errInexistantFile
*/

#pragma once

#include "error.hpp"

class ErrorInexistantFile: public Error
{
    public:
        inline ErrorInexistantFile(std::string filepath, const char *file, int line): Error(ConcatOnTheFly() << "Can't find file at: " << filepath, file, line) {};
};