/*
** EPITECH PROJECT, 2021
** contants
** File description:
** contants
*/

#include "../define.hpp"

#ifndef CONTANTS_HPP_
#define CONTANTS_HPP_

#define HP_LOST_AFTER_COLLISION 1

//do not change unless you really know what you are doing!
#define LENGTH_UDP_MESSAGE 18

//do not change unless you really know what you are doing!
#define LENGTH_TCP_MESSAGE 41

//DO NOT CHANGE UNDER ANY CIRCUMSTANCES!
//The default udp port should stay at 0 to let the pc choose what port to use
#define DEFAULT_UDP_PORT 0

//define the max number of players per saloon, 1is the minimum
#define MAX_PLAYER_PER_SALOON (Max_Default_Player_Per_Saloon > 0 ? Max_Default_Player_Per_Saloon : 4)

//DO NOT CHANGE UNDER ANY CIRCUMSTANCES!
//define how fast the server will try to run, 0 is the minimum
#define MASTER_CLOCK_SPEED_MILLISEC (Master_Clock_Speed_Millisec > 0 ? Master_Clock_Speed_Millisec : 1)

//DO NOT CHANGE UNDER ANY CIRCUMSTANCES!
//a clock based on the master clock, tick every x time the master clock ticks
#define PREDICTOR_CLOCK_FREQUENCY (Predictor_Clock_Sub_Frequancy > 0 ? Predictor_Clock_Sub_Frequancy : 1)

//DO NOT CHANGE UNDER ANY CIRCUMSTANCES!
//regulate the frequency at which the physicsystem send message
#define PHYSIC_SYSTEM_CLOCK_FREQUENCY (PREDICTOR_CLOCK_FREQUENCY * (PHYSIC_SYSTEM_SUB_CLOCK > 0 ? PHYSIC_SYSTEM_SUB_CLOCK : 5))

#endif