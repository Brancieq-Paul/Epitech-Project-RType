/*
** EPITECH PROJECT, 2021
** Velocity
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

class Velocity {
    public:
        Velocity(int vx, int vy) : vx_(vx), vy_(vy) {};
        ~Velocity() {};

        int getVx() { return (vx_); };
        int getVy() { return (vy_); };
        void setVx(int x) { vx_ = x; };
        void setVy(int y) { vy_ = y; };

    private:
        int vx_;
        int vy_;
};

#endif