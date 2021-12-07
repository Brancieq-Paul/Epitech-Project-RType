/*
** EPITECH PROJECT, 2021
** Clock
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <chrono>
#include <thread>
#include "notifiableByClock.hpp"
#include "../constantsServer.hpp"

namespace Clock {

    class AClock {
        public:
            AClock(NotifiableByClock *nc) : ticks(0), nc_(nc) {};
            ~AClock() {};

            void deactivate() {
                isDead = true;
            };
            virtual void tick() = 0;
            bool isDead = false;

        protected:
            unsigned long ticks;
            NotifiableByClock *nc_;
    };

    class MasterClock;

    class MasterClockSingleton
    {
        private:
            static MasterClock *instance;
            static std::mutex mutex_;

        protected:
            MasterClockSingleton() {};
            ~MasterClockSingleton() {};

        public:
            MasterClockSingleton(MasterClockSingleton &other) = delete;
            void operator=(const MasterClockSingleton &) = delete;
            static MasterClock *getInstance(boost::asio::io_service &io);
            static MasterClock *getInstance2();
    };

    class MasterClock {

        friend MasterClock *MasterClockSingleton::getInstance(boost::asio::io_service &io);

        protected:
            MasterClock(int frequency, boost::asio::io_service &io);

        public:
            ~MasterClock();
            void run();
            void addClock(AClock *newClock);

        private:
            void notify();
            void wait(const boost::system::error_code& error);

            boost::asio::io_service &io_;
            int frequency_;
            std::vector<AClock *> clocks;
            std::vector<int> deadClocks;
            unsigned long long timeElapsed;
            boost::asio::steady_timer timer_;
    };

    class BasicClock : public AClock {
        public:
            BasicClock(unsigned int subFreq, NotifiableByClock *nc) : AClock::AClock(nc), subFreq_(subFreq) {};
            ~BasicClock() {};

            void tick() {
                ticks++;
                if (ticks >= subFreq_) {
                    ticks -= subFreq_;
                    nc_->notifiedByClock();
                }
            };

        private:
            unsigned int subFreq_;
    };

    class StartableClock : public AClock {
        public:
            StartableClock(unsigned int subFreq, NotifiableByClock *nc) : AClock::AClock(nc), subFreq_(subFreq) {};
            ~StartableClock() {};

            void tick() {
                if (!start)
                    return;
                ticks++;
                if (ticks >= subFreq_) {
                    ticks -= subFreq_;
                    nc_->notifiedByClock();
                    start = false;
                }
            };


            void startClock() { start = true; };

        private:
            unsigned int subFreq_;
            bool start = false;
    };
};

#endif