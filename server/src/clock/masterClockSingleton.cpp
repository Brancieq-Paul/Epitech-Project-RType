/*
** EPITECH PROJECT, 2021
** MasterClockSingleton
** File description:
** MasterClockSingleton
*/

#include "../../include/clock/clock.hpp"

Clock::MasterClock *Clock::MasterClockSingleton::instance{nullptr};
std::mutex Clock::MasterClockSingleton::mutex_;

Clock::MasterClock *Clock::MasterClockSingleton::getInstance(boost::asio::io_service &io)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr)
    {
        instance = new Clock::MasterClock(MASTER_CLOCK_SPEED_MILLISEC, io);
    }
    return (instance);
}

Clock::MasterClock *Clock::MasterClockSingleton::getInstance2()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance != nullptr)
    {
        return (instance);
    }
    return (NULL);
}