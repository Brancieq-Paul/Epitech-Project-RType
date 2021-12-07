/*
** EPITECH PROJECT, 2021
** ColBox
** File description:
** ColBox
*/

#ifndef COL_BOX_HPP_
#define COL_BOX_HPP_

class ColBox {
    public:
        ColBox(int dimx, int dimy, int layers) : dimx_(dimx), dimy_(dimy), layers_(layers) {};
        ~ColBox() {};

        int getX() { return (dimx_); };
        int getY() { return (dimy_); };
        int getLayers() { return (layers_); };

        void killColBox() {
            dimx_ = 0;
            dimy_ = 0;
            layers_ = 0;
        };

    private:
        int dimx_;
        int dimy_;
        int layers_;
};

#endif