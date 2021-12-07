/*
** EPITECH PROJECT, 2021
** Predictor
** File description:
** Predictor
*/

#include "../../../../include/server/saloons/predictionSystem/predictorTheMagnificient.hpp"
#include "../../../../include/verbose.hpp"

Predictor::Predictor(std::shared_ptr<SaloonDB> db) : db_(db)
{

    boost::asio::io_service io;
    Clock::BasicClock *clockTmp = new Clock::BasicClock(PREDICTOR_CLOCK_FREQUENCY, this);
    clock = std::unique_ptr<Clock::BasicClock>(clockTmp);
    Clock::MasterClockSingleton::getInstance(io)->addClock(clockTmp);
};

void Predictor::notifiedByClock()
{
    if (started)
        simulateAllEntities();
};

void Predictor::start()
{
    started = true;
};

void Predictor::simulateAllEntities()
{
    auto es = db_->getEntities();
    for (auto e : es)
    {
        e->simulate(worldBoundaryX, worldBoundaryY);
    }
};