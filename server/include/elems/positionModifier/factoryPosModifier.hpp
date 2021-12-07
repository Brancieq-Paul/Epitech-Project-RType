/*
** EPITECH PROJECT, 2021
** FactoryPosModifier
** File description:
** FactoryPosModifier
*/

#ifndef FACTORY_POS_POS_MODIFIER_HPP_
#define FACTORY_POS_POS_MODIFIER_HPP_

#include "aPositionModifier.hpp"
#include <vector>
#include <memory>
#include "modifiers/linear.hpp"
#include "modifiers/controledByPlayer.hpp"
#include "modifiers/circle.hpp"
#include "../../data/message.hpp"

class FactoryPosModifier {

    private:
        FactoryPosModifier() {};
        ~FactoryPosModifier() {};
    public:
        enum PosModifierType {
            STATIONARY = 1,
            LINEAR = 2,
            CONTROLLED = 3,
            CIRCLE = 4
        };

        static std::shared_ptr<APositionModifier> createAPosModifier(PosModifierType type, std::vector<uint8_t> d) {
            switch (type) {
            case FactoryPosModifier::LINEAR:
                return (std::shared_ptr<APositionModifier>(new Linear(new Velocity((int8_t) d[0], (int8_t) d[1]), message::uint84ToUint(d[2], d[3], d[4], d[5]), message::uint84ToUint(d[6], d[7], d[8], d[9]))));
            case FactoryPosModifier::CONTROLLED:
                return (std::shared_ptr<APositionModifier>(new ControlledByPlayer()));
            case FactoryPosModifier::CIRCLE:
                return (std::shared_ptr<APositionModifier>(new Circle(message::uint84ToInt(d[0], d[1], d[2], d[3]), message::uint82Toint16(d[4], d[5]), message::uint82Toint16(d[6], d[7]), message::uint82Toint16(d[8], d[9]))));
            default:
                return (std::shared_ptr<APositionModifier>(new Stationary()));
            }
        };

        static PosModifierType getType(int type) {
            switch (type) {
                case LINEAR:
                    return (LINEAR);
                case CONTROLLED:
                    return (CONTROLLED);
                case CIRCLE:
                    return (CIRCLE);
                default:
                    return (STATIONARY);
            }
        };
};

#endif