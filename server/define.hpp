/*
** EPITECH PROJECT, 2021
** Verbose
** File description:
** Verbose
*/

#ifndef DEFINE_HPP_
#define DEFINE_HPP_

//POSITIVE INTEGER: define the max number of players per saloon, 1 is the minimum (4 is recommended)
#define Max_Default_Player_Per_Saloon 4

//POSITIVE INTEGER: define how fast the server will try to run, 1 is the minimum
#define Master_Clock_Speed_Millisec 2

//POSITIVE INTEGER: a clock based on the master clock, tick every x time the master clock ticks
#define Predictor_Clock_Sub_Frequancy 4

//POSITIVE INTEGER: define how often the physicSystem will notifyeach client of what happened,
//the number is the number of 'Predictor_Clock_Sub_Frequancy' cycle that will be skipped
#define PHYSIC_SYSTEM_SUB_CLOCK 8

#endif
