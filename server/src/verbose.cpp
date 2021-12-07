/*
** EPITECH PROJECT, 2021
** Verbose
** File description:
** Verbose
*/

#include "../include/verbose.hpp"

Verbose::Speaker *Verbose::SpeakerSingleton::instance{nullptr};
std::mutex Verbose::SpeakerSingleton::mutex_;

Verbose::Speaker *Verbose::SpeakerSingleton::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr)
    {
        instance = new Verbose::Speaker();
    }
    return (instance);
};