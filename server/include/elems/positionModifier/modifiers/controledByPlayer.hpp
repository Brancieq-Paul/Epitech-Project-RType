/*
** EPITECH PROJECT, 2021
** ControlledByPlayer
** File description:
** ControlledByPlayer
*/

#ifndef CONTROLLED_BY_PLAYER_HPP_
#define CONTROLLED_BY_PLAYER_HPP_

#include "../aPositionModifier.hpp"
#include <string>
#include "../../../verbose.hpp"

class ControlledByPlayer : public APositionModifier {
    public:
        ControlledByPlayer() : APositionModifier(CREATION_TIME_DOESNT_MATTER,ModifierType::CONTROLLED) {};

        inline bool modifyPos(std::shared_ptr<Pos> p, std::shared_ptr<Velocity> v) {
            p->setX(p->getX() + v->getVx());
            p->setY(p->getY() + v->getVy());
            return (true);
        };
};

#endif