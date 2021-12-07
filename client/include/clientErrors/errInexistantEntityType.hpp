/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** errInexistantFile
*/

#pragma once

#include "error.hpp"

class ErrorInexistantEntityType: public Error
{
    public:
        inline ErrorInexistantEntityType(int type, const char *file, int line): Error(ConcatOnTheFly() << "Can't find json map for entity type " << type, file, line) {};
};