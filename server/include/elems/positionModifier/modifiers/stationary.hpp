/*
** EPITECH PROJECT, 2021
** Stationary
** File description:
** Stationary
*/

#ifndef STATIONARY_HPP_
#define STATIONARY_HPP_

#include "../aPositionModifier.hpp"

class Stationary : public APositionModifier {
    public:
        Stationary() : APositionModifier(CREATION_TIME_DOESNT_MATTER, ModifierType::STATIONARY) {};

        inline bool modifyPos(std::shared_ptr<Pos> oldPos, std::shared_ptr<Velocity> velocity) { return (false); };
};

#endif