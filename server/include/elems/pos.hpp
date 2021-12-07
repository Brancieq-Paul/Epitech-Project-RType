/*
** EPITECH PROJECT, 2021
** Pos
** File description:
** Pos
*/

#ifndef POS_HPP_
#define POS_HPP_

class Pos {
    public:
        Pos(int x, int y) : x_(x), y_(y) {};
        ~Pos() {};

        int getX() { return (x_); };
        int getY() { return (y_); };
        void setX(int x) { x_ = x; };
        void setY(int y) { y_ = y; };

    private:
        int x_;
        int y_;
};

#endif