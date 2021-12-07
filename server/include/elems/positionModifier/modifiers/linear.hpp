/*
** EPITECH PROJECT, 2021
** Linear
** File description:
** Linear
*/

#ifndef LINEAR_HPP_
#define LINEAR_HPP_

#include "../aPositionModifier.hpp"

class Linear : public APositionModifier {
    public:
        Linear(Velocity *vel, uint boundx, uint boundy) : APositionModifier(CREATION_TIME_DOESNT_MATTER, ModifierType::LINEAR), ownVelocity(std::unique_ptr<Velocity>(vel)), boundx_(boundx), boundy_(boundy) {
            dirx = 1;
            diry = 1;
        };

        inline bool modifyPos(std::shared_ptr<Pos> pos, std::shared_ptr<Velocity> vel) {
            oldPosx = pos->getX();
            oldPosy = pos->getY();
            pos->setX(changePosX(pos->getX(), vel->getVx()));
            pos->setY(changePosY(pos->getY(), vel->getVy()));
            if (pos->getX() == oldPosx)
                dirx *= -1;
            if (pos->getY() == oldPosy)
                diry *= -1;
            return (true);
        };

    private:
        int changePosX(int posx, int velx) {
            if (!xSet)
                initx = posx;
            posx += velx * dirx;
            if (boundx_ == 0)
                return (posx);
            if (posx > initx + boundx_) {
                dirx *= -1;
                return (initx + boundx_);
            }
            if (posx < initx - boundx_) {
                dirx *= -1;
                return (initx - boundx_);
            }
            return (posx);
        };

        int changePosY(int posy, int vely) {
            if (!ySet)
                inity = posy;
            posy += vely * diry;
            if (boundy_ == 0)
                return (posy);
            if (posy > initx + boundy_) {
                diry *= -1;
                return (initx + boundy_);
            }
            if (posy < inity - boundy_) {
                diry *= -1;
                return (inity - boundy_);
            }
            return (posy);
        };

        std::unique_ptr<Velocity> ownVelocity;
        bool xSet = false;
        bool ySet = false;
        int oldPosx;
        int oldPosy;
        uint boundx_;
        uint boundy_;
        int dirx;
        int diry;
        int initx;
        int inity;
};

#endif