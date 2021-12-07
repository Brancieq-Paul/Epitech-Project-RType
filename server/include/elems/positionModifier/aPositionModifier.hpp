/*
** EPITECH PROJECT, 2021
** APositionModifier
** File description:
** APositionModifier
*/

#ifndef POSITION_MODIFIER_HPP_
#define POSITION_MODIFIER_HPP_

#define TIME unsigned long long
#define CREATION_TIME_DOESNT_MATTER 0

#include "../pos.hpp"
#include "../velocity.hpp"
#include <memory>

class APositionModifier {
    public:

        enum ModifierType {
            STATIONARY = 1,
            CONTROLLED = 3,
            LINEAR = 2,
            CIRCULAR = 4
        };

        APositionModifier(TIME creation_time, ModifierType type_) : creation_time_(creation_time), type(type_) {};
        ~APositionModifier() = default;

        virtual bool modifyPos(std::shared_ptr<Pos> oldPos, std::shared_ptr<Velocity> velocity) = 0;
        virtual ModifierType getType() { return (type); };

        protected:
            TIME creation_time_;
            ModifierType type;

};

#endif