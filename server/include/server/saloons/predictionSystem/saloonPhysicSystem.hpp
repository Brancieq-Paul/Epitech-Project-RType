/*
** EPITECH PROJECT, 2021
** SaloonPhysicSystem
** File description:
** SaloonPhysicSystem
*/

#ifndef SALOON_PHYSIC_SYSTEM_HPP_
#define SALOON_PHYSIC_SYSTEM_HPP_

#include "saloonDB.hpp"
#include "predictorTheMagnificient.hpp"
#include <memory>
#include "../../../clock/notifiableByClock.hpp"
#include "../../../clock/clock.hpp"
#include "../../../constantsServer.hpp"
#include "../../../verbose.hpp"

class Saloon;

class SaloonPhysicSystem : public NotifiableByClock{
    public:
        SaloonPhysicSystem(Saloon *saloon);
        ~SaloonPhysicSystem() {};

        void notifiedByClock();

        std::shared_ptr<SaloonDB> getDB() { return (db); };
        inline void startClock() {
            predictor->start();
        };

        void setBoundaries(int x, int y) {
            predictor->setWorldBoundaries(x, y);
        };

        void deactivate() {
            clock->deactivate();
            predictor->deactivate();
        };

    private:

        void prepareData();

        Saloon *saloon_;
        std::shared_ptr<SaloonDB> db;
        std::unique_ptr<Predictor> predictor;
        Clock::BasicClock *clock;
};

#endif