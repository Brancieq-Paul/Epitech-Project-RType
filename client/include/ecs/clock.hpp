/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** clock
*/

#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

namespace rtype
{
    namespace clock
    {
        class RClock
        {
            public:
                RClock(int delay_ms);
                ~RClock();

                bool deadLinePassed() const;
                void reset();
                float getRatio() const;

                static void restartCount();
                static void destroy();

            protected:
                int delay_ms_;
                int timeElapsed;

                static sf::Clock *clock_;
                static int globalTime;

                static std::vector<rtype::clock::RClock *> all_clocks_;
        };
    };
};