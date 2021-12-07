/*
** EPITECH PROJECT, 2021
** Predictor
** File description:
** Predictor
*/

#ifndef PREDICTOR_HPP_
#define PREDICTOR_HPP_

#include "saloonDB.hpp"
#include "../../../clock/notifiableByClock.hpp"
#include <memory>
#include "../../../clock/clock.hpp"
#include <iostream>
#include "../../../constantsServer.hpp"

class Predictor : public NotifiableByClock {
    public:
        Predictor(std::shared_ptr<SaloonDB> db);
        ~Predictor() {};

        void notifiedByClock();

        void start();

        void setWorldBoundaries(int x, int y) {
            worldBoundaryX = x;
            worldBoundaryY = y;
        };

        void deactivate() {
            clock->deactivate();
        };

    private:
        void simulateAllEntities();

        std::shared_ptr<SaloonDB> db_;
        std::unique_ptr<Clock::BasicClock> clock;
        bool started = false;
        int worldBoundaryX = -1;
        int worldBoundaryY = -1;
};

#endif