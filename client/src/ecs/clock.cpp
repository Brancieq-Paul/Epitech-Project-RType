/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** clock
*/

#include "ecs/clock.hpp"
#include <algorithm>
#include <iostream>

sf::Clock *rtype::clock::RClock::clock_ = new sf::Clock;
std::vector<rtype::clock::RClock *> rtype::clock::RClock::all_clocks_ = std::vector<rtype::clock::RClock *>();
int rtype::clock::RClock::globalTime = 0;

rtype::clock::RClock::RClock(int delay_ms) : delay_ms_(delay_ms)
{
    timeElapsed = 0;
    all_clocks_.push_back(this);
}

rtype::clock::RClock::~RClock()
{
    all_clocks_.erase(std::remove(all_clocks_.begin(), all_clocks_.end(), this), all_clocks_.end());
    if (all_clocks_.size() == 0)
        delete clock_;
}

bool rtype::clock::RClock::deadLinePassed() const
{
    return (timeElapsed >= delay_ms_);
}

float rtype::clock::RClock::getRatio() const
{
    return (timeElapsed / delay_ms_);
}

void rtype::clock::RClock::reset()
{
    timeElapsed = 0;
}

void rtype::clock::RClock::restartCount()
{
    globalTime = clock_->restart().asMilliseconds();
    for (auto it = all_clocks_.begin(); it != all_clocks_.end(); it++)
    {
        (*it)->timeElapsed += globalTime;
    }
}

void rtype::clock::RClock::destroy()
{
    delete clock_;
}