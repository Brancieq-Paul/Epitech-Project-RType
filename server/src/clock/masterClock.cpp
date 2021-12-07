/*
** EPITECH PROJECT, 2021
** MasterClock
** File description:
** MasterClock
*/

#include "../../include/clock/clock.hpp"
#include <iostream>
#include "../../include/verbose.hpp"

Clock::MasterClock::MasterClock(int frequency, boost::asio::io_service &io) : timer_(io), io_(io), timeElapsed(0), frequency_(frequency > 0 ? frequency : 1) {};

Clock::MasterClock::~MasterClock(){};

void Clock::MasterClock::run()
{
    timer_.expires_after(boost::asio::chrono::milliseconds{frequency_});
    timer_.async_wait(boost::bind(&Clock::MasterClock::wait, this, boost::asio::placeholders::error));
};

void Clock::MasterClock::addClock(AClock *newClock) { clocks.emplace_back(newClock); };

void Clock::MasterClock::notify()
{
    for (int i = 0; i < clocks.size(); i++)
    {
        if (clocks[i] == nullptr || clocks[i]->isDead)
        {
            deadClocks.emplace_back(i);
            continue;
        }
        clocks[i]->tick();
    }
    if (deadClocks.size() > 0)
    {
        for (int c = deadClocks.size() - 1; c > -1; c--)
            clocks.erase(clocks.begin() + c);
        deadClocks.clear();
    }
};

void Clock::MasterClock::wait(const boost::system::error_code& error)
{
    if (error == boost::asio::error::operation_aborted)
        Verbose::debugCriticalMessage("Master Clock failed", __FILE__, __LINE__);
    timer_.expires_after(boost::asio::chrono::milliseconds{frequency_});
    timer_.async_wait(boost::bind(&Clock::MasterClock::wait, this, boost::asio::placeholders::error));

    timeElapsed += 1;
    if (timeElapsed < 0) {
        timeElapsed = 0;
        Verbose::simpleDebugMessageWithColor("The master clock timer as reset to 0!", Verbose::RED, true);
    }
    notify();
};