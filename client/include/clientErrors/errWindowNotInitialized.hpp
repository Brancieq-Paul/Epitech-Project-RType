/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** errInexistantFile
*/

#pragma once

#include "error.hpp"

class ErrorWindowNotInitialized: public Error
{
    public:
        inline ErrorWindowNotInitialized(const char *file, int line): Error("Trying to get window before initialization.", file, line) {};
};