/*
** EPITECH PROJECT, 2021
** NotifiableByClock
** File description:
** NotifiableByClock
*/

#ifndef NOTIFIABLE_BY_CLOCK_HPP_
#define NOTIFIABLE_BY_CLOCK_HPP_

class NotifiableByClock
{
    public:
        ~NotifiableByClock() = default;
        virtual void notifiedByClock() = 0;
};

#endif