/*
** EPITECH PROJECT, 2021
** Circle
** File description:
** Circle
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include "../aPositionModifier.hpp"

class Circle : public APositionModifier {
    public:
        Circle(int radius, int16_t radialSpeed, int16_t actionRadius, int16_t startingPos) : APositionModifier(CREATION_TIME_DOESNT_MATTER, ModifierType::CIRCULAR) {};

        inline bool modifyPos(std::shared_ptr<Pos> oldPos, std::shared_ptr<Velocity> velocity) {
            return (false);
        };
};

#endif