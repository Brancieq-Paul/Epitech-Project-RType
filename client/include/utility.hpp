/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** utility
*/

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <stdio.h>
#include <string.h>
#include "message.hpp"
#include "entity.hpp"

namespace rtype
{
    namespace utility
    {
        enum idComponent
        {
            SPRITE,
            TRANSFORM
        };

        enum keyCode
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            EXIT_ALL,
            DEL,
            SPACE,
            MOUSE_RELEASED,
            UNKNOWN
        };

        static bool isDirectionnal(keyCode code)
        {
            if (code == UP || code == DOWN || code == LEFT || code == RIGHT)
            {
                return true;
            }
            return false;
        }
    }
}

#endif /* !UTILITY_HPP_ */
