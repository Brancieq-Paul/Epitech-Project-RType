/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-martin.ferrand
** File description:
** processor
*/

#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include "ecs/entity.hpp"

namespace rtype
{
    namespace processor
    {
        enum ResponseType
        {
            PosEntity = 2,
            StatusEntity = 4,
            NONE_UDP
        };

        enum ResponseTypeTCP
        {
            GameLaunched = 2,
            IdSalon = 4,
            SomeoneJoinSalon = 6,
            SomeoneQuitSalon = 8,
            PortUDP = 13,
            SalonIsFull = 15,
            NONE_TCP
        };

        class MyProcess
        {
        public:
            inline MyProcess(){};
            inline ~MyProcess(){};
            inline void setEntityList(std::vector<rtype::entity::REntity> *new_list) { _entity_list = new_list; };
            void processTCP(uint8_t *data);
            void processUDP(uint8_t *data);

        private:
            rtype::entity::REntity *findEntity(uint8_t *data);
            void setPosEntity(rtype::entity::REntity *obj, uint8_t *data);
            void setPlayerInOrder(uint8_t *data);
            void setLife(rtype::entity::REntity *obj, uint8_t *data);
            void setPortUDP(uint8_t *data);

            std::vector<rtype::entity::REntity> *_entity_list;
        };
    }
}

#endif /* !PROCESSOR_HPP_ */
